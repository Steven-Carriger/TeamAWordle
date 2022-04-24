#include "WordleDisplayControl.h"

#include <algorithm>
#include <iostream>
using namespace std;

#include <FL/Fl_Box.H>

#define DISPLAY_GAP 5

namespace view
{

WordleDisplayControl::WordleDisplayControl(int x, int y, int width, int height, int guessLimit, int wordLength)  : Fl_Group(x, y, width, height, nullptr)
{
    this->currLetter = 0;
    this->currWord = 0;
    this->guessLimit = guessLimit;
    this->wordLength = wordLength;
    this->guessing = true;
    begin();
    this->createGrid();
    end();
}

WordleDisplayControl::~WordleDisplayControl()
{
    //dtor
}

void WordleDisplayControl::createGrid()
{
    int boxSize = min((this->w() - (this->wordLength - 1) * DISPLAY_GAP) / this->wordLength, (this->h() - (this->guessLimit - 1) * DISPLAY_GAP)/ this->guessLimit);
    int initX = this->x() + (this->w() - (this->wordLength - 1) * DISPLAY_GAP - wordLength * boxSize) / 2;
    int initY = this->y() + (this->h() - (this->guessLimit - 1) * DISPLAY_GAP - guessLimit * boxSize) / 2;
    for (int i = 0; i < guessLimit * wordLength; i++)
    {
        this->boxs.push_back(new Fl_Box(Fl_Boxtype::FL_BORDER_BOX, initX + (i % wordLength) * (boxSize + DISPLAY_GAP), initY + (i / wordLength) * (boxSize + DISPLAY_GAP), boxSize, boxSize, ""));
    }
}

bool WordleDisplayControl::addLetter(const char* letter)
{
    if (this->guessing && this->currLetter < this->wordLength * (this->currWord + 1))
    {
        this->child(this->currLetter)->label(letter);
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
        this->currLetter--;
        return true;
    }
    return false;
}

void WordleDisplayControl::submitWord(vector<WordleManager::LetterState> wordState)
{
    if (!this->guessing || this->currLetter == 0 || this->currLetter % this->wordLength != 0) return;
    int currIndx = this->currWord * this->wordLength;
    bool isAllCorrect = true;
    for (auto aState = wordState.begin(); aState != wordState.end(); ++aState)
    {
        if (*aState == WordleManager::LetterState::CORRECT)
        {
            this->child(currIndx)->color(FL_GREEN);
        }
        else if (*aState == WordleManager::LetterState::IN_WORD)
        {
            this->child(currIndx)->color(FL_YELLOW);
            isAllCorrect = false;
        }
        else if (*aState == WordleManager::LetterState::NOT_IN_WORD)
        {
            this->child(currIndx)->color(FL_GRAY);
            isAllCorrect = false;
        }
        currIndx++;
    }
    this->currWord++;
    this->guessing = !isAllCorrect || this->currWord == 6;
    this->redraw();
}

}
