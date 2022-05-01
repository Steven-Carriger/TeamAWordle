#include "SettingsWindow.h"

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 300
#define WINDOW_TITLE " Settings"
#define BUTTON_WIDTH 70
#define BUTTON_HEIGHT 30
namespace view
{

/**
* Creates a new SettingsWindow
*
* @param setting the setting to set by value
*/
SettingsWindow::SettingsWindow(bool setting) : Fl_Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE)
{
    begin();
    this->okButton = new Fl_Button(WINDOW_WIDTH / 2 - 35, WINDOW_HEIGHT - 45, BUTTON_WIDTH, BUTTON_HEIGHT, "OK");
    this->okButton->callback(cbOk, this);
    this->allowReuseButton = new Fl_Check_Button(WINDOW_WIDTH / 2 - BUTTON_WIDTH, WINDOW_HEIGHT / 3, BUTTON_WIDTH * 2, BUTTON_HEIGHT, "Allow letter reuse");
    this->allowReuseButton->type(FL_TOGGLE_BUTTON);
    this->allowReuseButton->value(setting);
    end();
}

/**
* The event handler for when the ok button is clicked
*
* @param widget the button that was invoked
* @param data the window or group that contains the button invoked
*/
void SettingsWindow::cbOk(Fl_Widget* widget, void* data)
{
    SettingsWindow* window = (SettingsWindow*)data;
    window->hide();
}

/**
* gets if the reuse of letters is allowed or not
*
* @return true if reuse is allowed, false otherwise
*/
bool SettingsWindow::isReuseAllowed()
{
    return this->allowReuseButton->value();
}

/**
* Settings Window deconstructor
*/
SettingsWindow::~SettingsWindow()
{
    //dtor
}

}
