#ifndef WORDLEDISPLAYCONTROL_H
#define WORDLEDISPLAYCONTROL_H

#include <string>
using namespace std;

#include <FL/Fl_Group.H>

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
    string guessWord;
    string guess;

public:
    WordleDisplayControl(int x, int y, int width, int height, int guessLimit, int wordLength);
    virtual ~WordleDisplayControl();
    bool addLetter(const char* letter);
    bool removeLetter();
    bool submitWord();

};

};

#endif // WORDLEDISPLAYCONTROL_H
