#include "WordleDisplayControl.h"

#include <algorithm>
#include <iostream>
using namespace std;

#include <FL/Fl_Box.H>

#define DISPLAY_GAP 5

namespace view
{

/**
* Creates a new WordleDisplayControl
*
* @param x the x value of the control
* @param y the y value of the control
* @param width the width of the control
* @param height the height of the control
* @param guessLimit the guessLimit for the display
* @param wordLength the wordLength of the words to display
*/
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

/**
* WordleDisplayControl deconstructor
*/
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

/**
* Adds a letter to the display
*
* @param letter the letter to add
*
* @return true if the letter is added, false otherwise
*/
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

/**
* Removes the most recently added letter
*
* @return true if a letter is removed, false otherwise
*/
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

/**
* Submits the word to this display
*
* @param wordState the states of the letters to determine how to display them
* @param statsManager the manager to use if the game is finishes after this word is submitted
*/
void WordleDisplayControl::submitWord(vector<WordleManager::LetterState> wordState, StatisticsManager* statsManager)
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
    this->guessing = !isAllCorrect && this->currWord != 6;
    this->redraw();
    if (!this->guessing)
    {
        statsManager->increasePlayersStats(isAllCorrect, this->currWord);
    }
}

}
