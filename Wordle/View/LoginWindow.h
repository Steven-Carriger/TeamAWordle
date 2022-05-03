#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <Fl/Fl_Window.H>
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Input.H>

#include <string>
using namespace std;

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 300
#define LOGIN_TITLE "Login"
#define LOGIN_BUTTON_WIDTH 70
#define LOGIN_BUTTON_HEIGHT 30
#define LOGIN_BUTTON_X 165
#define LOGIN_BUTTON_Y 255
#define INPUT_X 260
#define INPUT_Y 100
#define EMPTY_STRING " "
namespace view
{

class LoginWindow : public Fl_Window
{
private:
    Fl_Button* loginButton;
    Fl_Input* userNameInput;
public:
    LoginWindow();
    virtual ~LoginWindow();
    string getUserName();
private:
    static void cbLogin(Fl_Widget* widget, void* data);
};

}
#endif // LOGINWINDOW_H
