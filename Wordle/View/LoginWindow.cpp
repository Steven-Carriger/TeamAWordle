#include "LoginWindow.h"

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 300
#define WINDOW_TITLE "Login"
#define BUTTON_WIDTH 70
#define BUTTON_HEIGHT 30
namespace view
{

LoginWindow::LoginWindow() : Fl_Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE)
{
    this->loginButton = new Fl_Button(WINDOW_WIDTH / 2 - 35, WINDOW_HEIGHT - 45, BUTTON_WIDTH, BUTTON_HEIGHT, "Login");
    this->loginButton->callback(cbLogin, this);
    this->userNameInput = new Fl_Input(WINDOW_WIDTH - BUTTON_WIDTH * 2, WINDOW_HEIGHT / 3, BUTTON_WIDTH, BUTTON_HEIGHT, "Please enter your username:");
}

void LoginWindow::cbLogin(Fl_Widget* widget, void* data)
{
    LoginWindow* window = (LoginWindow*) data;
    if (window->userNameInput->value() == "")
    {
        return;
    }
    window->hide();
}

string LoginWindow::getUserName()
{
    return this->userNameInput->value();
}

LoginWindow::~LoginWindow()
{
    //dtor
}

}
