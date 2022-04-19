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

namespace view
{

class WordleWindow : public Fl_Window
{
    public:
        WordleWindow(int, int, const char*);
        virtual ~WordleWindow();
};
}
#endif // WORDLEWINDOW_H
