#include "WordleWindow.h"

namespace view
{

/**
* Creates a new WordleWindow
*
* @param width the width of the window
* @param height the height of the window
* @param title the title of the window
*/
WordleWindow::WordleWindow(int width, int height, const char* title) : Fl_Window(width, height, title)
{
    this->setUpManagers();
    begin();
    this->displayControl = new WordleDisplayControl(PADDING, PADDING, width - 2 * PADDING, (height - PADDING) / 2, GUESS_LIMIT, this->settingsManager->getWordLength());
    this->keyboardControl = new WordleKeyboardControl(PADDING, (height - PADDING) / 2, width - 2 * PADDING, height / 2);
    this->isReuseAllowed = false;
    this->setUpHandlers();
    this->setUpButtons();
    end();
}

void WordleWindow::handleLetterPress(WordleWindow* window, const char* key)
{
    if (window->displayControl->addLetter(key))
    {
        window->word.append(key);
    }
}

void WordleWindow::handleEnterPress(WordleWindow* window)
{
    if (window->manager->validateWord(window->word))
    {
        window->displayControl->submitWord(window->manager->getDetails(window->word), window->statisticsManager);
        window->keyboardControl->updateKeys(window->manager->getDetails(window->word), window->word);
        window->word = "";
    }
}

void WordleWindow::handleWin(WordleWindow* window, int wordCount)
{
    switch ( fl_choice("You Won! What do you want to do next?", "Logout", "Play Agian", "Exit") ) {
        case 0:
            {
                window->fileManager->saveUserData(window->statisticsManager);
                string user = window->displayUserLogin();
                window->statisticsManager->setCurrentUser(user);
                window->restart();
                break;
            }
        case 1:
            window->restart();
            break;
        case 2:
            window->hide();
            break;
    }
}

void WordleWindow::handleLoss(WordleWindow* window)
{
    const string word = window->manager->getCurrentWord();
    switch ( fl_choice("You Lost! The word was %s. What do you want to do?", "Logout", "Play Agian", "Exit", word.c_str()) ) {
        case 0: break;
        case 1: break;
        case 2: window->hide();
    }
}

void WordleWindow::handleBackPress(WordleWindow* window)
{
    if (window->displayControl->removeLetter())
    {
        window->word.pop_back();
    }
}

void WordleWindow::restart()
{
    this->displayControl->clean();
    this->keyboardControl->clean();
    this->manager->randomizeWord(5);
}

void WordleWindow::cbDisplayUserStats(Fl_Widget* widget, void* data)
{
    WordleWindow* window = (WordleWindow*) data;
    StatisticsWindow stats(window->statisticsManager);
    stats.set_modal();
    stats.show();

    while (stats.shown())
    {
        Fl::wait();
    }
}

void WordleWindow::cbSaveUserStats(Fl_Widget* widget, void* data)
{
    WordleWindow* window = (WordleWindow*) data;
    window->fileManager->saveUserData(window->statisticsManager);
}

void WordleWindow::cbDisplaySettings(Fl_Widget* widget, void* data)
{
    WordleWindow* window = (WordleWindow*) data;
    SettingsWindow settings(window->settingsManager);
    settings.set_modal();
    settings.show();

    while (settings.shown())
    {
        Fl::wait();
    }
    window->manager->setRepeatedLetters(settings.isReuseAllowed());
    window->settingsManager->setRepeatsAllowed(settings.isReuseAllowed());
    window->settingsManager->setWordLength(settings.getWordLength());
    window->fileManager->saveSettingsData(window->settingsManager);
    //window->restart();
}

string WordleWindow::displayUserLogin()
{
    LoginWindow loginWindow;
    loginWindow.set_modal();
    loginWindow.show();

    while (loginWindow.shown())
    {
        Fl::wait();
    }

    return loginWindow.getUserName();
}

void WordleWindow::setUpHandlers()
{
    this->keyboardControl->setLetterCallback(bind(handleLetterPress, this, _1));
    this->keyboardControl->setEnterCallback(bind(handleEnterPress, this));
    this->keyboardControl->setBackCallback(bind(handleBackPress, this));
    this->displayControl->setWinCallback(bind(handleWin, this, _1));
    this->displayControl->setLossCallback(bind(handleLoss, this));
}

void WordleWindow::setUpManagers()
{
    this->manager = new WordleManager();
    this->statisticsManager = new StatisticsManager();
    this->settingsManager = new SettingsManager();
    this->fileManager = new FileManager();

    this->fileManager->loadDictionary(this->manager);
    this->fileManager->loadSettingsData(this->settingsManager);
    this->fileManager->loadUserData(this->statisticsManager);

    this->statisticsManager->setCurrentUser(this->displayUserLogin());
    this->manager->randomizeWord(this->settingsManager->getWordLength());
    this->manager->setRepeatedLetters(this->settingsManager->isRepeatsAllowed());
    this->word = "";
}

void WordleWindow::setUpButtons()
{
    this->saveButton = new Fl_Button(BUTTON_X, PADDING, BUTTON_WIDTH, BUTTON_HEIGHT, "Save");
    this->settingsButton = new Fl_Button(BUTTON_X, PADDING + BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT, "Settings");
    this->statisticsButton = new Fl_Button(BUTTON_X, PADDING + BUTTON_HEIGHT + BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT, "Stats");

    this->saveButton->callback(cbSaveUserStats, this);
    this->settingsButton->callback(cbDisplaySettings, this);
    this->statisticsButton->callback(cbDisplayUserStats, this);
}

/**
* WordleWindow deconstructor
*/
WordleWindow::~WordleWindow()
{
}

}
