#include "WordleDisplayControl.h"

#include <algorithm>
#include <iostream>
using namespace std;

#include <FL/Fl_Box.H>

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

void WordleDisplayControl::setLossCallback(LossCallback callback)
{
    this->lossCallback = callback;
}

void WordleDisplayControl::setWinCallback(WinCallback callback)
{
    this->winCallback = callback;
}

void WordleDisplayControl::createGrid()
{
    int boxSize = min((this->w() - (this->wordLength - LETTER_VALUE) * DISPLAY_GAP) / this->wordLength, (this->h() - (this->guessLimit - LETTER_VALUE) * DISPLAY_GAP)/ this->guessLimit);
    int initX = this->x() + (this->w() - (this->wordLength - LETTER_VALUE) * DISPLAY_GAP - wordLength * boxSize) / 2;
    int initY = this->y() + (this->h() - (this->guessLimit - LETTER_VALUE) * DISPLAY_GAP - guessLimit * boxSize) / 2;
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
    if (this->guessing && this->currLetter < this->wordLength * (this->currWord + LETTER_VALUE))
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
    if (this->guessing && this->currWord * this->wordLength <= this->currLetter - LETTER_VALUE )
    {
        this->child(this->currLetter - LETTER_VALUE)->label(nullptr);
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
            this->child(currIndx)->color(FL_BLACK);
            this->child(currIndx)->labelcolor(FL_WHITE);
            isAllCorrect = false;
        }
        currIndx++;
    }
    this->currWord++;
    this->guessing = !isAllCorrect && this->currWord != GUESS_LIMIT;
    this->redraw();
    if (!this->guessing)
    {
      statsManager->increasePlayersStats(isAllCorrect, this->currWord);
    }
    if (isAllCorrect) this->winCallback(this->currWord);
    if (this->currWord == 6) this->lossCallback();
}

void WordleDisplayControl::clean()
{
    this->currLetter = 0;
    this->currWord = 0;
    this->guessing = true;
    for (int i = 0; i < guessLimit * wordLength; i++)
    {
        this->child(i)->label(nullptr);
        this->child(i)->color(FL_GRAY);
        this->child(i)->labelcolor(FL_BLACK);
    }
}

}
