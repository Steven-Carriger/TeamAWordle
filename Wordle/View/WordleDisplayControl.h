#ifndef WORDLEDISPLAYCONTROL_H
#define WORDLEDISPLAYCONTROL_H

#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>

#include <string>
#include <functional>
#include <algorithm>
#include <iostream>
using namespace std;

#include "WordleManager.h"
#include "StatisticsManager.h"
using namespace model;

#define DISPLAY_GAP 5
#define GUESS_LIMIT 6
#define LETTER_VALUE 1
namespace view
{

class WordleDisplayControl : private Fl_Group
{
public:
    typedef function<void()> LossCallback;
    typedef function<void(int)> WinCallback;
private:
    int guessLimit;
    int wordLength;
    int currLetter;
    int currWord;
    bool guessing;
    vector<Fl_Box*> boxs;
    LossCallback lossCallback;
    WinCallback winCallback;

public:
    WordleDisplayControl(int x, int y, int width, int height, int guessLimit, int wordLength);
    virtual ~WordleDisplayControl();
    bool addLetter(const char* letter);
    bool removeLetter();
    void setLossCallback(LossCallback callback);
    void setWinCallback(WinCallback callback);
    void clean();
    void submitWord(vector<WordleManager::LetterState> wordState, StatisticsManager* statsManager);
private:
    void createGrid();
};

};

#endif // WORDLEDISPLAYCONTROL_H
