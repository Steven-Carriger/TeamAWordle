#include "WordleWindow.h"
#include "WordleManager.h"
using namespace model;

#include <iostream>
using namespace std;

#define PADDING 20
namespace view
{

WordleWindow::WordleWindow(int width, int height, const char* title) : Fl_Window(width, height, title)
{
    begin();
    this->displayControl = new WordleDisplayControl(PADDING, PADDING, width - 2 * PADDING, (height - PADDING) / 2, 6, 5);
    this->keyboardControl = new WordleKeyboardControl(PADDING, (height - PADDING) / 2, width - 2 * PADDING, height / 2);
    end();
}

int WordleWindow::handle(int event)
{
    if (Fl_Group::handle(event))
    {
        return 1;
    }
    switch(event)
    {
    case FL_KEYBOARD:
        return handleKeyPressed(event);
    }
    return 0;
}

void WordleWindow::cbKeyPressed(Fl_Widget* widget, void* data)
{
    WordleWindow* window = (WordleWindow*) data;
    cout << "Help" << endl;
    window->handleInput(widget->label());
}

void WordleWindow::handleEnter() {
    WordleManager manager(5);
    if (!manager.validateWord(this->word)) {
        //TODO inform invalid word
        return;
    }
    cout << this->word << endl;
    this->displayControl->submitWord(manager.getDetails(this->word));

}

void WordleWindow::handleBack() {
    if (this->displayControl->removeLetter()) {
        this->word.pop_back();
    }
}

void WordleWindow::handleInput(const char* key)
{
    cout << "Key: " << key << " was pressed"<< endl;
    if (this->displayControl->addLetter(key)) {
        this->word.append(key);
    }
}

int WordleWindow::handleKeyPressed(int event)
{
    if (Fl::event_key() == FL_Enter)
    {
        this->handleInput("Enter");
        return 1;
    }
    if (Fl::event_key() == FL_BackSpace)
    {
        this->handleInput("Enter");
        return 1;
    }
    this->handleInput(Fl::event_text());
    return 1;
}

WordleWindow::~WordleWindow()
{
    //dtor
}
}
