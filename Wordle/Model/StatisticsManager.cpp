#include "StatisticsManager.h"

namespace model
{

/**
* Creates a new StatisticsManager
*/
StatisticsManager::StatisticsManager()
{
    this->userStats = map<string, Player*>();
}

/**
* Gets the current player the manager is tracking
*
* @return the current player
*/
Player* StatisticsManager::getCurrentPlayer()
{
    return this->currentPlayer;
}

/**
* gets the users the manager is storing
*
* @return the users the manager is storing
*/
map<string, Player*>& StatisticsManager::getUserStats()
{
    return this->userStats;
}

/**
* Sets the current user based on the provided userName
*
* @param userName the player to look for or create
*/
void StatisticsManager::setCurrentUser(string userName)
{
    if (!this->userStats.count(toLowerCase(userName)))
    {
        this->currentPlayer = new Player();
        this->currentPlayer->setUserName(toLowerCase(userName));
        this->userStats[toLowerCase(userName)] = this->currentPlayer;
        return;
    }
    this->currentPlayer = this->userStats[toLowerCase(userName)];
}

/**
* Increases the players stats based on if they won or not.
*
* @param didWin determines if the player won or not
* @param timesGuessed the amount of times the user guessed to win or lose
*/
void StatisticsManager::increasePlayersStats(bool didWin, int timesGuessed)
{
    if (didWin)
    {
        this->currentPlayer->setCurrentWinStreak(this->currentPlayer->getCurrentWinStreak() + WIN_VALUE);
        this->currentPlayer->setTotalWins(this->currentPlayer->getTotalWins() + WIN_VALUE);
        this->currentPlayer->setGuessCountAtIndex(timesGuessed - WIN_VALUE, this->currentPlayer->getAmountOfGuessesAtIndex(timesGuessed - WIN_VALUE) + WIN_VALUE);
    }
    else
    {
        this->currentPlayer->setCurrentWinStreak(LOSS_STREAK_VALUE);
    }
    this->currentPlayer->setTotalGames(this->currentPlayer->getTotalGames() + WIN_VALUE);
}

/**
* The StatisticsManager deconstructor
*/
StatisticsManager::~StatisticsManager()
{
    //dtor
}

}
