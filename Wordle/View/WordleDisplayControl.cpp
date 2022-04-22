#include "WordleDisplayControl.h"


#include <algorithm>
#include <iostream>
using namespace std;

#include <FL/Fl_Box.H>

namespace view
{

WordleDisplayControl::WordleDisplayControl(int x, int y, int width, int height, int guessLimit, int wordLength)  : Fl_Group(x, y, width, height, nullptr)
{
    this->currLetter = 0;
    this->currWord = 0;
    this->guessLimit = guessLimit;
    this->wordLength = wordLength;
    this->guessing = true;
    int boxSize = min(width / wordLength, height / guessLimit);
    int initX = (width - wordLength * boxSize) / 2;
    int initY = (height - guessLimit * boxSize) / 2;
    for (int i = 0; i < guessLimit * wordLength; i++)
    {
        this->add(new Fl_Box(Fl_Boxtype::FL_BORDER_BOX, initX + (i % wordLength) * boxSize, initY + (i / wordLength) * boxSize, boxSize, boxSize, ""));
    }
    this->guessWord = "TESTS";
    this->guess = "";
}

WordleDisplayControl::~WordleDisplayControl()
{
    //dtor
}

bool WordleDisplayControl::addLetter(const char* letter)
{

    if (this->guessing && this->currLetter < this->wordLength * (this->currWord + 1))
    {
        this->child(this->currLetter)->label(letter);
        this->guess.push_back(letter[0]);
        this->currLetter++;
        return true;
    }
    return false;
}

bool WordleDisplayControl::removeLetter()
{
    if (this->guessing && this->currWord * this->wordLength <= this->currLetter - 1 )
    {
        this->child(this->currLetter - 1)->label(nullptr);
        this->guess.pop_back();
        cout << this->guess << endl;
        this->currLetter--;
        return true;
    }
    return false;
}

bool WordleDisplayControl::submitWord()
{
    //TODO check if valid word
    //cout << this->guess << endl;
    bool valid = true;
    if (valid && this->guess.length() == this->wordLength)
    {

        //TODO bring this to model
        bool correct = (this->guess == this->guessWord);
        if (correct) {
            this->guessing = false;
        }
        this->guess.erase();
        this->currWord++;
        cout << this->currWord << endl;
        if (this->currWord == this->guessLimit)
        {
            this->guessing = false;
        }
        return true;
    }
    return false;

}

}
