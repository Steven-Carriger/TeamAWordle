#include "StatisticsWindow.h"

namespace view
{

/**
* Creates a new StatisticsWindow
*
* @param manager the StatisticsManager to extract information from to display
*/
StatisticsWindow::StatisticsWindow(StatisticsManager* manager) : Fl_Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE)
{
    begin();

    this->okButton = new Fl_Button(OK_BUTTON_X, OK_BUTTON_Y, STATS_BUTTON_WIDTH, STATS_BUTTON_HEIGHT, "OK");
    this->okButton->callback(cbOk, this);

    this->totalGameOutput = new Fl_Output(TOTAL_GAME_X, TOTAL_GAME_Y, OUTPUT_WIDTH, OUTPUT_HEIGHT, "Your total game(s) are: ");
    this->winRateOutput = new Fl_Output(WINRATE_X, WINRATE_Y, OUTPUT_WIDTH, OUTPUT_HEIGHT, "Your win rate is: ");
    this->winStreakOutput = new Fl_Output(WINSTREAK_X, WINSTREAK_Y, OUTPUT_WIDTH, OUTPUT_HEIGHT, "Your win streak is: ");
    this->highestWinStreakOutput = new Fl_Output(HIGHEST_STREAK_X, HIGHEST_STREAK_Y, OUTPUT_WIDTH, OUTPUT_HEIGHT, "Your highest win streak is: ");

    this->guessDistributionBuffer = new Fl_Text_Buffer();
    this->guessDistributionDisplay = new Fl_Text_Display(DISPLAY_TEXT_POSITION, DISPLAY_TEXT_POSITION, DISPLAY_TEXT_WIDTH, DISPLAY_TEXT_HEIGHT);
    this->guessDistributionDisplay->textfont(FL_COURIER);
    this->guessDistributionDisplay->buffer(this->guessDistributionBuffer);

    this->setDisplayValues(manager);
    end();

}

void StatisticsWindow::setDisplayValues(StatisticsManager* manager)
{
    Player* currentPlayer = manager->getCurrentPlayer();

    string totalGames = to_string(currentPlayer->getTotalGames());
    this->totalGameOutput->value(totalGames.c_str());
    string winRate = to_string((int)currentPlayer->calculateWinRate()) + "%";
    this->winRateOutput->value(winRate.c_str());
    string winStreak = to_string(currentPlayer->getCurrentWinStreak());
    this->winStreakOutput->value(winStreak.c_str());
    string highestStreak = to_string(currentPlayer->getHighestWinStreak());
    this->highestWinStreakOutput->value(highestStreak.c_str());

    string guessDistributionSummary = "Guess Distribution: \n";
    for (int index = 0; index < MAX_GUESS; index++)
    {
        string distributionLine = "On guess " + to_string(index + INDEX_VALUE) + ": " +to_string(currentPlayer->getAmountOfGuessesAtIndex(index)) + " times.";
        guessDistributionSummary += distributionLine + "\n";
    }
    this->guessDistributionBuffer->text(guessDistributionSummary.c_str());
}

/**
* The event handler for when the ok button is clicked
*
* @param widget the button that was invoked
* @param data the window or group that contains the button invoked
*/
void StatisticsWindow::cbOk(Fl_Widget* widget, void* data)
{
    StatisticsWindow* window = (StatisticsWindow*)data;
    window->hide();
}

/**
* Destructor that cleans up all allocated resources for the window
*/
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
