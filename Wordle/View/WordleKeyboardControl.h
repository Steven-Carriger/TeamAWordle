#ifndef WORDLEKEYBOARDCONTROL_H
#define WORDLEKEYBOARDCONTROL_H

#include <vector>
#include <functional>
#include <string.h>
#include <bits/stdc++.h>
using namespace std;

#include "WordleManager.h"
using namespace model;

#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Widget.H>

namespace view
{

class WordleKeyboardControl : private Fl_Group
{
public:
    typedef function<void(const char*)> LetterCallback;
    typedef function<void()> EnterCallback;
    typedef function<void()> BackCallback;
private:
    vector<Fl_Button*> buttons;
    LetterCallback letterCallback;
    EnterCallback enterCallback;
    BackCallback backCallback;
public:
    WordleKeyboardControl(int x, int y, int width, int height);
    virtual ~WordleKeyboardControl();
    void setLetterCallback(LetterCallback callback);
    void setEnterCallback(EnterCallback callback);
    void setBackCallback(BackCallback callback);
    void updateKeys(vector<WordleManager::LetterState> wordState, const string& userWord);
    void clean();
private:
    void createButtons();
    void setKeyStatus(Fl_Button* key, WordleManager::LetterState letterState);
    Fl_Button* getKeyWithLetter(const char letter);
    static void handleLetterPress(Fl_Widget* sender);
    static void handleEnterPress(Fl_Widget* sender);
    static void handleBackPress(Fl_Widget* sender);
};

};

#endif // WORDLEKEYBOARDCONTROL_H
