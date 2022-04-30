#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <Fl/Fl_Window.H>
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Input.H>

#include <string>
using namespace std;

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
