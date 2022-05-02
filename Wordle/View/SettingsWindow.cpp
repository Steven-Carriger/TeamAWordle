#include "SettingsWindow.h"

namespace view
{

/**
* Creates a new SettingsWindow
*
* @param setting the setting to set by value
*/
SettingsWindow::SettingsWindow(bool setting) : Fl_Window(WINDOW_WIDTH, WINDOW_HEIGHT, SETTINGS_TITLE)
{
    begin();
    this->okButton = new Fl_Button(SETTINGS_BUTTON_X, SETTINGS_BUTTON_Y, SETTINGS_BUTTON_WIDTH, SETTINGS_BUTTON_HEIGHT, "OK");
    this->okButton->callback(cbOk, this);
    this->allowReuseButton = new Fl_Check_Button(REUSE_BUTTON_X, REUSE_BUTTON_Y, REUSE_WIDTH, SETTINGS_BUTTON_HEIGHT, "Allow letter reuse");
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
