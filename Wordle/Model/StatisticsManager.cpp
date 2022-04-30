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
        cout << this->userStats.size() << endl;
        return;
    }
    this->currentPlayer = this->userStats[toLowerCase(userName)];
}

StatisticsManager::~StatisticsManager()
{
    //dtor
}

}
