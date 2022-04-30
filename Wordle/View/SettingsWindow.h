#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <Fl/Fl_Window.H>
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Check_Button.H>
#include <iostream>
#include <string>
using namespace std;

namespace view
{

class SettingsWindow : public Fl_Window
{
private:
    Fl_Button* okButton;
    Fl_Check_Button* allowReuseButton;
public:
    SettingsWindow(bool setting);
    virtual ~SettingsWindow();
    static void cbOk(Fl_Widget* widget, void* data);
    bool isReuseAllowed();
};

}
#endif // SETTINGSWINDOW_H
