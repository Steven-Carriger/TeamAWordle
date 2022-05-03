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
    this->displayControl = new WordleDisplayControl(PADDING, PADDING, width - 2 * PADDING, (height - 2 * PADDING - BUTTON_HEIGHT - 2 * GAP) / 2, GUESS_LIMIT, this->settingsManager->getWordLength());
    this->keyboardControl = new WordleKeyboardControl(PADDING, (height - 2 * PADDING - BUTTON_HEIGHT - 2 * GAP) / 2 + PADDING + GAP, width - 2 * PADDING, (height - 2 * PADDING - BUTTON_HEIGHT - 2 * GAP) / 2);
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
        window->keyboardControl->updateKeys(window->manager->getDetails(window->word), window->word);
        window->displayControl->submitWord(window->manager->getDetails(window->word));
        window->word = "";
    }
}

void WordleWindow::handleWin(WordleWindow* window, int wordCount)
{
    showEndPopup(window, "You Won! What do you want to do next?", nullptr);
    window->statisticsManager->increasePlayersStats(true, wordCount);
}

void WordleWindow::handleLoss(WordleWindow* window)
{
    string word = window->manager->getCurrentWord();
    showEndPopup(window, "You Lost! The word was %s. What do you want to do?", word.c_str());
    window->statisticsManager->increasePlayersStats(false, 7);
}

void WordleWindow::showEndPopup(WordleWindow* window, const char* endMessage, const void* endData)
{
    switch ( fl_choice(endMessage, "Logout", "Play Agian", "Exit", endData) ) {
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

void WordleWindow::handleBackPress(WordleWindow* window)
{
    if (window->displayControl->removeLetter())
    {
        window->word.pop_back();
    }
}

void WordleWindow::restart()
{
    this->displayControl->clean(this->settingsManager->getWordLength());
    this->keyboardControl->clean();
    this->manager->randomizeWord(this->settingsManager->getWordLength());
    this->word = "";
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

void WordleWindow::cbLogout(Fl_Widget* widget, void* data)
{
    WordleWindow* window = (WordleWindow*) data;
    window->fileManager->saveUserData(window->statisticsManager);
    string user = window->displayUserLogin();
    window->statisticsManager->setCurrentUser(user);
    window->restart();
}

void WordleWindow::cbRestart(Fl_Widget* widget, void* data)
{
    WordleWindow* window = (WordleWindow*) data;
    window->restart();
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
    if (settings.isShouldRestart()) {
        window->manager->setRepeatedLetters(settings.isReuseAllowed());
        window->settingsManager->setRepeatsAllowed(settings.isReuseAllowed());
        window->settingsManager->setWordLength(settings.getWordLength());
        window->fileManager->saveSettingsData(window->settingsManager);
        window->restart();
    }
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
    this->logoutButton = new Fl_Button((this->w() - 4 * BUTTON_WIDTH - 4 * GAP) / 2, this->h() - PADDING - BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT, "Logout");
    this->settingsButton = new Fl_Button((this->w() - 4 * BUTTON_WIDTH - 4 * GAP) / 2 + BUTTON_WIDTH + GAP, this->h() - PADDING - BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT, "Settings");
    this->statisticsButton = new Fl_Button((this->w() - 4 * BUTTON_WIDTH - 4 * GAP) / 2 + 2 * BUTTON_WIDTH + 2 * GAP, this->h() - PADDING - BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT, "Stats");
    this->restartButton = new Fl_Button((this->w() - 4 * BUTTON_WIDTH - 4 * GAP) / 2 + 3 * BUTTON_WIDTH + 3 * GAP, this->h() - PADDING - BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT, "Restart");

    this->logoutButton->callback(cbLogout, this);
    this->restartButton->callback(cbRestart, this);
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
