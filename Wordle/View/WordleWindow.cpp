#include "WordleWindow.h"
#include "WordleManager.h"
using namespace model;

#include <iostream>
#include <functional>
using namespace std;
using namespace std::placeholders;

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
}

void WordleWindow::handleLetterPress(WordleWindow* window, const char* key)
{
    window->displayControl->addLetter(key);
}


void WordleWindow::handleEnterPress(WordleWindow* window)
{
    //TODO
}

void WordleWindow::handleBackPress(WordleWindow* window)
{
    window->displayControl->removeLetter();
}

WordleWindow::~WordleWindow()
{
}

}
