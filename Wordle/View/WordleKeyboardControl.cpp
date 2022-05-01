#include "WordleKeyboardControl.h"

#define KEYBOARD_GAP 5
#define NON_LETTER_LENGTH 15
#define NUM_FIRST_ROW 10
#define NUM_OTHER_ROW 9
#define NUM_ROW 3

#include <algorithm>
#include <iostream>
using namespace std;

#include "Utils.h"

namespace view
{

/**
* Creates a new WordleKeyboardControl
*
* @param x the x value of the control
* @param y the y value of the control
* @param width the width of the control
* @param height the height of the control
*/
WordleKeyboardControl::WordleKeyboardControl(int x, int y, int width, int height) : Fl_Group(x, y, width, height, nullptr)
{
    begin();
    this->createButtons();
    end();
}

/**
* The WordleKeyboardControl deconstructor
*/
WordleKeyboardControl::~WordleKeyboardControl()
{
    //dtor
}

void WordleKeyboardControl::createButtons()
{
    int keySize = min((this->w() - NUM_FIRST_ROW * KEYBOARD_GAP) / NUM_FIRST_ROW, (this->h() - NUM_ROW * KEYBOARD_GAP) / NUM_ROW);
    int initXFirstRow = this->x() + (this->w() - (NUM_FIRST_ROW - 1) * KEYBOARD_GAP - NUM_FIRST_ROW * keySize) / 2;
    int initXOtherRow = this->x() + (this->w() - (NUM_OTHER_ROW - 1) * KEYBOARD_GAP - NUM_OTHER_ROW * keySize) / 2;
    int initY = this->y() + (this->h() - (NUM_ROW - 1) * KEYBOARD_GAP - NUM_ROW * keySize) / 2;
    vector<const char*> keyLabels = {"Q","W","E","R","T","Y","U","I","O","P","A","S","D","F","G","H","J","K","L","ENTER","Z","X","C","V","B","N","M","BACK"};
    int row = 0;

    for (int i = 0; i < keyLabels.size(); i++)
    {
        int x = initXFirstRow;
        int colMod = i % NUM_FIRST_ROW;
        if (i >= NUM_FIRST_ROW)
        {
            x = initXOtherRow;
            colMod = (i - NUM_FIRST_ROW) % NUM_OTHER_ROW;
            row = (i - NUM_FIRST_ROW) / NUM_OTHER_ROW + 1;

        }

        Fl_Button* newKeyButton;
        if (keyLabels[i] == "ENTER")
        {
            newKeyButton = new Fl_Button(x + colMod * (keySize + KEYBOARD_GAP) - NON_LETTER_LENGTH, initY + row * (keySize + KEYBOARD_GAP), keySize + NON_LETTER_LENGTH, keySize, keyLabels[i]);
            newKeyButton->callback(handleEnterPress);
            newKeyButton->shortcut(FL_Enter);
        }
        else if (keyLabels[i] == "BACK")
        {
            newKeyButton = new Fl_Button(x + colMod * (keySize + KEYBOARD_GAP), initY + row * (keySize + KEYBOARD_GAP), keySize + NON_LETTER_LENGTH, keySize, keyLabels[i]);
            newKeyButton->callback(handleBackPress);
            newKeyButton->shortcut(FL_BackSpace);
        }
        else
        {
            newKeyButton = new Fl_Button(x + colMod * (keySize + KEYBOARD_GAP), initY + row * (keySize + KEYBOARD_GAP), keySize, keySize, keyLabels[i]);
            newKeyButton->callback(handleLetterPress);
            newKeyButton->shortcut(tolower(keyLabels[i][0]));
        }

        this->buttons.push_back(newKeyButton);
    }
}

/**
* Sets the current call back based on the provided call back
*
* @param letterCallback the LetterCallback to set to
*/
void WordleKeyboardControl::setLetterCallback(LetterCallback letterCallback)
{
    this->letterCallback = letterCallback;
}

/**
* Sets the current call back based on the provided call back
*
* @param enterCallback the EnterCallback to set to
*/
void WordleKeyboardControl::setEnterCallback(EnterCallback enterCallback)
{
    this->enterCallback = enterCallback;
}

/**
* Sets the current call back based on the provided call back
*
* @param backCallback the BackCallback to set to
*/
void WordleKeyboardControl::setBackCallback(BackCallback backCallback)
{
    this->backCallback = backCallback;
}

void WordleKeyboardControl::handleLetterPress(Fl_Widget* sender)
{
    WordleKeyboardControl* keyboard = (WordleKeyboardControl*) sender->parent();
    keyboard->letterCallback(sender->label());
}

void WordleKeyboardControl::handleEnterPress(Fl_Widget* sender)
{
    WordleKeyboardControl* keyboard = (WordleKeyboardControl*) sender->parent();
    keyboard->enterCallback();
}

void WordleKeyboardControl::handleBackPress(Fl_Widget* sender)
{
    WordleKeyboardControl* keyboard = (WordleKeyboardControl*) sender->parent();
    keyboard->backCallback();
}


/**
* updates the display of the keys based on the state of the letters
*
* @param wordState a collection of states based on the provided word
* @param userWord the word the user provided
*/
void WordleKeyboardControl::updateKeys(vector<WordleManager::LetterState> wordState, const string& userWord)
{
    for (int currIndx = 0; currIndx < userWord.length(); currIndx++)
    {
        Fl_Button* button = this->getKeyWithLetter(userWord[currIndx]);
        if (button != nullptr)
        {
            this->setKeyStatus(button, wordState[currIndx]);
        }
    }
    this->redraw();
}

void WordleKeyboardControl::setKeyStatus(Fl_Button* key, WordleManager::LetterState letterState)
{
    if (key->color() == FL_GREEN)
    {
        return;
    }
    switch (letterState)
    {
    case WordleManager::LetterState::CORRECT:
        key->color(FL_GREEN);
        return;
    case WordleManager::LetterState::IN_WORD:
        key->color(FL_YELLOW);
        return;
    case WordleManager::LetterState::NOT_IN_WORD:
        if (key->color() != FL_GRAY)
        {
            return;
        }
        key->color(FL_BLACK);
        key->labelcolor(FL_WHITE);
        return;
    }
}

Fl_Button* WordleKeyboardControl::getKeyWithLetter(const char letter)
{
    for (Fl_Button* button : this->buttons)
    {
        if (toLowerCase(button->label()) == toLowerCase(&letter))
        {
            return button;
        }
    }
    return nullptr;
}

}
