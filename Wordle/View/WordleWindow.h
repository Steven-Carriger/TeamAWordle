#ifndef WORDLEWINDOW_H
#define WORDLEWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Button.H>

#include "string.h"
#include <ctype.h>
#include <iostream>
#include <vector>
#include <iostream>
#include <functional>
using namespace std;
using namespace std::placeholders;

#include "WordleManager.h"
#include "SettingsManager.h"
using namespace model;

#include "WordleDisplayControl.h"
#include "WordleKeyboardControl.h"
#include "StatisticsWindow.h"
#include "SettingsWindow.h"
#include "LoginWindow.h"
#include "FileManager.h"

#define PADDING 20
#define GUESS_LIMIT 6
#define WORD_LENGTH 5
#define BUTTON_HEIGHT 25
#define BUTTON_X 440
#define BUTTON_WIDTH 60
namespace view
{

class WordleWindow : public Fl_Window
{
private:
    WordleManager* manager;
    StatisticsManager* statisticsManager;
    SettingsManager* settingsManager;
    FileManager* fileManager;
    string word;
    bool isReuseAllowed;
    WordleDisplayControl* displayControl;
    WordleKeyboardControl* keyboardControl;
    Fl_Button* saveButton;
    Fl_Button* settingsButton;
    Fl_Button* statisticsButton;
    void setUpKeyboardHandlers();
    void setUpManagers();
    void setUpButtons();
    string displayUserLogin();
public:
    WordleWindow(int x, int y, const char* title);
    virtual ~WordleWindow();
private:
    static void cbDisplayUserStats(Fl_Widget* widget, void* data);
    static void cbSaveUserStats(Fl_Widget* widget, void* data);
    static void cbDisplaySettings(Fl_Widget* widget, void* data);
    static void handleLetterPress(WordleWindow* window, const char* key);
    static void handleEnterPress(WordleWindow* window);
    static void handleBackPress(WordleWindow* window);
};
}
#endif // WORDLEWINDOW_H
