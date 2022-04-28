#include "StatisticsManager.h"

namespace model
{

StatisticsManager::StatisticsManager(string userName)
{
    this->userStats = map<string, Player>();
    this->loadUserData();
    this->setCurrentUser(userName);
}

void StatisticsManager::loadUserData()
{

}

Player* StatisticsManager::getCurrentPlayer()
{
    return &this->currentPlayer;
}

void StatisticsManager::setCurrentUser(string userName)
{
    if (!this->userStats.count(userName))
    {
        this->currentPlayer = Player();
        this->currentPlayer.setUserName(userName);
        return;
    }
    this->currentPlayer = this->userStats[userName];
}

StatisticsManager::~StatisticsManager()
{
    //dtor
}

}
