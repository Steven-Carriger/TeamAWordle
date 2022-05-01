#ifndef WORDLEDISPLAYCONTROL_H
#define WORDLEDISPLAYCONTROL_H

#include <string>
#include <functional>
using namespace std;

#include "WordleManager.h"
using namespace model;

#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>

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
    void submitWord(vector<WordleManager::LetterState> wordState);
    void setLossCallback(LossCallback callback);
    void setWinCallback(WinCallback callback);
    void clean();
private:
    void createGrid();
};

};

#endif // WORDLEDISPLAYCONTROL_H
