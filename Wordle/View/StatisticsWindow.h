#ifndef STATISTICSWINDOW_H
#define STATISTICSWINDOW_H

#include <Fl/Fl_Window.H>
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Output.H>
#include <Fl/Fl_Text_Buffer.H>
#include <Fl/Fl_Text_Display.H>

#include "StatisticsManager.h"
using namespace model;

#include <string>
using namespace std;

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 300
#define WINDOW_TITLE "Your Stats"
#define STATS_BUTTON_WIDTH 70
#define STATS_BUTTON_HEIGHT 30
#define MAX_GUESS 6
#define OK_BUTTON_X 165
#define OK_BUTTON_Y 255
#define OUTPUT_HEIGHT 20
#define OUTPUT_WIDTH 50
#define TOTAL_GAME_X 275
#define TOTAL_GAME_Y 0
#define WINRATE_X 225
#define WINRATE_Y 25
#define WINSTREAK_X 240
#define WINSTREAK_Y 50
#define HIGHEST_STREAK_X 295
#define HIGHEST_STREAK_Y 75
#define DISPLAY_TEXT_POSITION 100
#define DISPLAY_TEXT_WIDTH 200
#define DISPLAY_TEXT_HEIGHT 150
#define INDEX_VALUE 1
namespace view
{

class StatisticsWindow : public Fl_Window
{

private:
    StatisticsManager* manager;
    Fl_Button* okButton;
    Fl_Output* totalGameOutput;
    Fl_Output* winRateOutput;
    Fl_Output* winStreakOutput;
    Fl_Output* highestWinStreakOutput;
    Fl_Text_Buffer* guessDistributionBuffer;
    Fl_Text_Display* guessDistributionDisplay;

    void setDisplayValues(StatisticsManager* manager);
public:
    StatisticsWindow(StatisticsManager* manager);
    virtual ~StatisticsWindow();
    static void cbOk(Fl_Widget* widget, void* data);
    void setWidgetValues();
};

}
#endif // STATISTICSWINDOW_H
