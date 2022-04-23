#ifndef WORDLEKEYBOARDCONTROL_H
#define WORDLEKEYBOARDCONTROL_H

#include <vector>
using namespace std;

#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>

namespace view {

class WordleKeyboardControl : private Fl_Group
{
    private:
        vector<Fl_Button*> buttons;
    public:
        WordleKeyboardControl(int x, int y, int width, int height);
        virtual ~WordleKeyboardControl();
    private:
        void createButtons();
};

};

#endif // WORDLEKEYBOARDCONTROL_H
