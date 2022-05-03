#include "SettingsWindow.h"

#include "Utils.h"

#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT 200
#define WINDOW_TITLE " Settings"
#define INPUT_WIDTH 70
#define INPUT_HEIGHT 30
#define GAP 10
namespace view
{

/**
* Creates a new SettingsWindow
*
* @param setting the setting to set by value
*/
SettingsWindow::SettingsWindow(SettingsManager* manager) : Fl_Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE)
{
    begin();
    this->manager = manager;
    int pad = (WINDOW_HEIGHT - 3 * INPUT_HEIGHT - 2 * GAP) / 2;
    this->okButton = new Fl_Button(WINDOW_WIDTH / 2 - INPUT_WIDTH / 2, pad + 2 * GAP + 2 * INPUT_HEIGHT, INPUT_WIDTH, INPUT_HEIGHT, "OK");
    this->okButton->callback(cbOk, this);
    this->allowReuseButton = new Fl_Check_Button(WINDOW_WIDTH / 2 - INPUT_WIDTH / 2, pad, INPUT_HEIGHT, INPUT_HEIGHT, "Allow Repeat Letters");
    this->allowReuseButton->type(FL_TOGGLE_BUTTON);
    this->allowReuseButton->value(manager->isRepeatsAllowed());
    this->wordLengthComboBox = new Fl_Input_Choice(WINDOW_WIDTH / 2 - INPUT_WIDTH / 2, pad + GAP + INPUT_HEIGHT, INPUT_WIDTH, INPUT_HEIGHT, "Word Length: ");
    this->wordLengthComboBox->add("4");
    this->wordLengthComboBox->add("5");
    this->wordLengthComboBox->add("6");
    this->wordLengthComboBox->add("7");
    this->wordLengthComboBox->value("5");
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

int SettingsWindow::getWordLength()
{
    return utils::toInt(this->wordLengthComboBox->value(), "Invalid Word Length");
}

/**
* Settings Window deconstructor
*/
SettingsWindow::~SettingsWindow()
{
    //dtor
}

}
