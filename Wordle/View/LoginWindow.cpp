#include "LoginWindow.h"

namespace view
{

/**
* Creates a new Login Window
*/
LoginWindow::LoginWindow() : Fl_Window(WINDOW_WIDTH, WINDOW_HEIGHT, LOGIN_TITLE)
{
    this->loginButton = new Fl_Button(LOGIN_BUTTON_X, LOGIN_BUTTON_Y, LOGIN_BUTTON_WIDTH, LOGIN_BUTTON_HEIGHT, "Login");
    this->loginButton->callback(cbLogin, this);
    this->userNameInput = new Fl_Input(INPUT_X, INPUT_Y, LOGIN_BUTTON_WIDTH, LOGIN_BUTTON_HEIGHT, "Please enter your username:");
}

void LoginWindow::cbLogin(Fl_Widget* widget, void* data)
{
    LoginWindow* window = (LoginWindow*) data;
    if (window->userNameInput->value() == EMPTY_STRING)
    {
        return;
    }
    window->hide();
}

/**
* gets the user name that was entered
*
* @return the user name entered
*/
string LoginWindow::getUserName()
{
    return this->userNameInput->value();
}

/**
* This is a Login Window Deconstructor
*/
LoginWindow::~LoginWindow()
{
    //dtor
}

}
