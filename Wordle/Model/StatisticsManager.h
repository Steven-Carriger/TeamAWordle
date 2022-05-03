#ifndef STATISTICSMANAGER_H
#define STATISTICSMANAGER_H

#include <map>
#include <string>
using namespace std;

#include "Utils.h"
using namespace utils;

#include "Player.h"

#define WIN_VALUE 1
#define LOSS_STREAK_VALUE 0
namespace model
{
class StatisticsManager
{
private:
    map<string, Player*> userStats;
    Player* currentPlayer;
    void loadUserData();
public:
    StatisticsManager();
    virtual ~StatisticsManager();
    Player* getCurrentPlayer();
    void saveUserData();
    void setCurrentUser(string userName);
    void addUser(string userName, Player* user);
    map<string, Player*>& getUserStats();
    void increasePlayersStats(bool didWin, int timesGuessed);
};
}
#endif // STATISTICSMANAGER_H
