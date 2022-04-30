#ifndef STATISTICSMANAGER_H
#define STATISTICSMANAGER_H

#include <map>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

#include "Utils.h"
using namespace utils;

#include "Player.h"

namespace model
{

class StatisticsManager
{
private:
    map<string, Player*> userStats;
    Player* currentPlayer;
    void loadUserData();
    void setCurrentUser(string userName);
public:
    StatisticsManager(string userName);
    virtual ~StatisticsManager();
    Player* getCurrentPlayer();
    void saveUserData();
    void addUser(string userName, Player* user);
};

}
#endif // STATISTICSMANAGER_H
