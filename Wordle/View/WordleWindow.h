#ifndef WORDLEWINDOW_H
#define WORDLEWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Button.H>

#include "string.h"
#include <ctype.h>
#include <iostream>
#include <vector>
using namespace std;

namespace view
{

class WordleWindow : public Fl_Window
{
private:
    vector<Fl_Button*> keyButtons;
    vector<char*> keyLabels;
    static void cbKeyPressed(Fl_Widget*, void*);
    int handle(int event);
    int handleKeyPressed(int event);
    void handleInput(const char*);
    void createTheKeyboard();
    void addKeysToTheKeyboard();
public:
    WordleWindow(int, int, const char*);
    virtual ~WordleWindow();
};
}
#endif // WORDLEWINDOW_H
