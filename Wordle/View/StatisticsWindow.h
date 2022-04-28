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
    void setOKLocation(int x, int y);
    static void cbOk(Fl_Widget* widget, void* data);
    void setWidgetValues();
};

}
#endif // STATISTICSWINDOW_H
