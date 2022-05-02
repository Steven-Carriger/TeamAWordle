#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <Fl/Fl_Window.H>
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Check_Button.H>

#include <string>
using namespace std;

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 300
#define SETTINGS_TITLE "Settings"
#define SETTINGS_BUTTON_WIDTH 70
#define SETTINGS_BUTTON_HEIGHT 30
#define SETTINGS_BUTTON_X 165
#define SETTINGS_BUTTON_Y 255
#define REUSE_BUTTON_X 130
#define REUSE_BUTTON_Y 100
#define REUSE_WIDTH 140
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
