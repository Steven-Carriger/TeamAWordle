#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <Fl/Fl_Window.H>
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Check_Button.H>
#include <FL/Fl_Input_Choice.H>

#include <string>
using namespace std;

#include "SettingsManager.h"
using namespace model;

#include "Utils.h"
using namespace utils;

#define SETTINGS_WINDOW_WIDTH 300
#define SETTINGS_WINDOW_HEIGHT 200
#define SETTINGS_WINDOW_TITLE "Settings"
#define INPUT_WIDTH 70
#define INPUT_HEIGHT 30
#define GAP 10
namespace view
{

class SettingsWindow : public Fl_Window
{
private:
    SettingsManager* manager;
    Fl_Button* okButton;
    Fl_Check_Button* allowReuseButton;
    Fl_Input_Choice* wordLengthComboBox;
    bool shouldRestart;
public:
    SettingsWindow(SettingsManager* manager);
    virtual ~SettingsWindow();
    static void cbOk(Fl_Widget* widget, void* data);
    bool isReuseAllowed();
    bool isShouldRestart();
    int getWordLength();
};

}
#endif // SETTINGSWINDOW_H
