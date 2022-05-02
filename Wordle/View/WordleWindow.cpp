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
    begin();
    this->displayControl = new WordleDisplayControl(PADDING, PADDING, width - 2 * PADDING, (height - PADDING) / 2, GUESS_LIMIT, WORD_LENGTH);
    this->keyboardControl = new WordleKeyboardControl(PADDING, (height - PADDING) / 2, width - 2 * PADDING, height / 2);
    this->isReuseAllowed = false;
    this->setUpKeyboardHandlers();
    this->setUpButtons();
    this->setUpManagers();
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

void WordleWindow::handleBackPress(WordleWindow* window)
{
    if (window->displayControl->removeLetter())
    {
        window->word.pop_back();
    }
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
    SettingsWindow settings(window->isReuseAllowed);
    settings.set_modal();
    settings.show();

    while (settings.shown())
    {
        Fl::wait();
    }
    window->isReuseAllowed = settings.isReuseAllowed();
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

void WordleWindow::setUpKeyboardHandlers()
{
    this->keyboardControl->setLetterCallback(bind(handleLetterPress, this, _1));
    this->keyboardControl->setEnterCallback(bind(handleEnterPress, this));
    this->keyboardControl->setBackCallback(bind(handleBackPress, this));
}

void WordleWindow::setUpManagers()
{
    this->manager = new WordleManager();
    this->statisticsManager = new StatisticsManager();
    this->fileManager = new FileManager();

    this->fileManager->loadDictionary(this->manager);
    this->fileManager->loadUserData(this->statisticsManager);

    this->statisticsManager->setCurrentUser(this->displayUserLogin());
    this->manager->randomizeWord(WORD_LENGTH);
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
