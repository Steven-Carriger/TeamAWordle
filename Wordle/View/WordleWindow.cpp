#include "WordleWindow.h"

#include <iostream>
#include <functional>
using namespace std;
using namespace std::placeholders;

#include <FL/fl_ask.H>

#define PADDING 20
namespace view
{

WordleWindow::WordleWindow(int width, int height, const char* title) : Fl_Window(width, height, title)
{
    begin();
    this->displayControl = new WordleDisplayControl(PADDING, PADDING, width - 2 * PADDING, (height - PADDING) / 2, 6, 5);
    this->keyboardControl = new WordleKeyboardControl(PADDING, (height - PADDING) / 2, width - 2 * PADDING, height / 2);
    end();
    this->keyboardControl->setLetterCallback(bind(handleLetterPress, this, _1));
    this->keyboardControl->setEnterCallback(bind(handleEnterPress, this));
    this->keyboardControl->setBackCallback(bind(handleBackPress, this));
    this->manager = new WordleManager();
    this->manager->randomizeWord(5);
    this->word = "";
    this->guessAmount = 0;
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
    //TODO: Make alerts as labels in the window and add restart abilty.
    if (window->manager->validateWord(window->word))
    {
        window->displayControl->submitWord(window->manager->getDetails(window->word));
        window->guessAmount++;
        if (window->manager->guessWord(window->word))
        {
            fl_alert("You won!");
        }
        cout << window->guessAmount << endl;
        if (window->guessAmount == 6) {
            fl_alert("You lose!");
        }
        window->word = "";
    }
    else
    {
        fl_alert("Not a valid word.");
    }
}

void WordleWindow::handleBackPress(WordleWindow* window)
{
    if (window->displayControl->removeLetter())
    {
        window->word.pop_back();
    }
}

WordleWindow::~WordleWindow()
{
}

}
