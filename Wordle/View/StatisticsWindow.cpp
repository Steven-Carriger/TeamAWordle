#include "StatisticsWindow.h"

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 300
#define WINDOW_TITLE "Your Stats"
#define BUTTON_WIDTH 70
#define BUTTON_HEIGHT 30
namespace view
{

// Constructs a statistics window creating and initializing all the widgets that will be displayed
//
// @precondition width > 0 AND height > 0
// @postcondition none
//
// @param width The width of the window
// @param height The height of the window
// @param title The title to display for the window
StatisticsWindow::StatisticsWindow() : Fl_Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE)
{

    begin();

    this->okButton = new Fl_Button(WINDOW_WIDTH / 2 - 35, WINDOW_HEIGHT - 45, BUTTON_WIDTH, BUTTON_HEIGHT, "OK");
    this->okButton->callback(cbOk, this);

    this->totalGameOutput = new Fl_Output(275, 0, 50, 20, "Your total game(s) are: ");
    this->winRateOutput = new Fl_Output(225, 25, 50, 20, "Your win rate is: ");
    this->winStreakOutput = new Fl_Output(240, 50, 50, 20, "Your win streak is: ");
    this->highestWinStreakOutput = new Fl_Output(295, 75, 50, 20, "Your highest win streak is: ");

    this->guessDistributionBuffer = new Fl_Text_Buffer();
    this->guessDistributionDisplay = new Fl_Text_Display(WINDOW_WIDTH / 2 - 100, 100, 200, 150);
    this->guessDistributionDisplay->textfont(FL_COURIER);
    this->guessDistributionDisplay->buffer(this->guessDistributionBuffer);

    end();

}

// The handler when OK is invoked
void StatisticsWindow::cbOk(Fl_Widget* widget, void* data)
{
    StatisticsWindow* window = (StatisticsWindow*)data;
    window->hide();
}

// Sets the (x,y) location of the OK button
//
// @precondition none
// @postcondition none
void StatisticsWindow::setOKLocation(int x, int y)
{
    this->okButton->position(x, y);
}

// Destructor that cleans up all allocated resources for the window
StatisticsWindow::~StatisticsWindow()
{
    delete this->okButton;
    delete this->totalGameOutput;
    delete this->winRateOutput;
    delete this->winStreakOutput;
    delete this->highestWinStreakOutput;
    delete this->guessDistributionDisplay;
}

}
