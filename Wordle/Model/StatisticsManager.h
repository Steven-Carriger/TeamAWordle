#ifndef STATISTICSMANAGER_H
#define STATISTICSMANAGER_H

#include <map>
using namespace std;

#include "Player.h"

namespace model
{

class StatisticsManager
{
private:
    map<string, Player> userStats;
    Player currentPlayer;
    void loadUserData();
    void setCurrentUser(string userName);
public:
    StatisticsManager(string userName);
    virtual ~StatisticsManager();
    Player* getCurrentPlayer();
};

}
#endif // STATISTICSMANAGER_H
