#include "StatisticsManager.h"

namespace model
{

StatisticsManager::StatisticsManager()
{
    this->userStats = map<string, Player*>();
}

Player* StatisticsManager::getCurrentPlayer()
{
    return this->currentPlayer;
}

map<string, Player*>& StatisticsManager::getUserStats()
{
    return this->userStats;
}

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

void StatisticsManager::increasePlayersStats(bool didWin, int timesGuessed)
{
    if (didWin)
    {
        this->currentPlayer->setCurrentWinStreak(this->currentPlayer->getCurrentWinStreak() + 1);
        this->currentPlayer->setTotalWins(this->currentPlayer->getTotalWins() + 1);
        this->currentPlayer->setGuessCountAtIndex(timesGuessed - 1, this->currentPlayer->getAmountOfGuessesAtIndex(timesGuessed - 1) + 1);
    }
    else
    {
        this->currentPlayer->setCurrentWinStreak(0);
    }
    this->currentPlayer->setTotalGames(this->currentPlayer->getTotalGames() + 1);
}

StatisticsManager::~StatisticsManager()
{
    //dtor
}

}
