#ifndef WORDLEDISPLAYCONTROL_H
#define WORDLEDISPLAYCONTROL_H

#include <string>
using namespace std;

#include "WordleManager.h"
#include "StatisticsManager.h"
using namespace model;

#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>

#define DISPLAY_GAP 5
#define GUESS_LIMIT 6
#define LETTER_VALUE 1
namespace view
{

class WordleDisplayControl : private Fl_Group
{
private:
    int guessLimit;
    int wordLength;
    int currLetter;
    int currWord;
    bool guessing;
    vector<Fl_Box*> boxs;

public:
    WordleDisplayControl(int x, int y, int width, int height, int guessLimit, int wordLength);
    virtual ~WordleDisplayControl();
    bool addLetter(const char* letter);
    bool removeLetter();
    void submitWord(vector<WordleManager::LetterState> wordState, StatisticsManager* statsManager);
private:
    void createGrid();
};

};

#endif // WORDLEDISPLAYCONTROL_H
