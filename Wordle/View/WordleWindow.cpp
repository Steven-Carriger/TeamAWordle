#include "WordleWindow.h"

#include <iostream>
#include <functional>
using namespace std;
using namespace std::placeholders;

#define PADDING 20
#define GUESS_LIMIT 6
#define WORD_LENGTH 5
#define BUTTON_HEIGHT 25
namespace view
{

WordleWindow::WordleWindow(int width, int height, const char* title) : Fl_Window(width, height, title)
{
    begin();
    this->displayControl = new WordleDisplayControl(PADDING, PADDING, width - 2 * PADDING, (height - PADDING) / 2, GUESS_LIMIT, WORD_LENGTH);
    this->keyboardControl = new WordleKeyboardControl(PADDING, (height - PADDING) / 2, width - 2 * PADDING, height / 2);

    this->saveButton = new Fl_Button(440, PADDING, 60, BUTTON_HEIGHT, "Save");
    this->settingsButton = new Fl_Button(440, PADDING + BUTTON_HEIGHT, 60, BUTTON_HEIGHT, "Settings");
    this->statisticsButton = new Fl_Button(440, PADDING + BUTTON_HEIGHT + BUTTON_HEIGHT, 60, BUTTON_HEIGHT, "Stats");
    this->saveButton->callback(cbSaveUserStats, this);
    this->settingsButton->callback(cbDisplaySettings, this);
    this->statisticsButton->callback(cbDisplayUserStats, this);

    this->isReuseAllowed = false;
    this->setUpKeyboardHandlers();
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
        window->displayControl->submitWord(window->manager->getDetails(window->word));
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
    settings.show();

    while (settings.shown())
    {
        Fl::wait();
    }
    window->isReuseAllowed = settings.isReuseAllowed();
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

    string test = "Alexander";
    this->statisticsManager->setCurrentUser(test);
    this->manager->randomizeWord(WORD_LENGTH);
    this->word = "";
}

WordleWindow::~WordleWindow()
{
}

}
