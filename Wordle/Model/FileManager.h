#ifndef FILEMANAGER_H
#define FILEMANAGER_H

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
#include "WordleManager.h"
#include "StatisticsManager.h"
#include "SettingsManager.h"

#define DICTIONARY_FILEPATH "dictionary.txt"
#define USER_STATISTICS_FILEPATH "userStats.csv"
#define STRING_CONVERSION_ERROR "Error converting a loaded in string to an integer."
#define USERNAME_INDEX 0
#define TOTAL_GAMES_INDEX 1
#define TOTAL_WINS_INDEX 2
#define WINSTREAK_INDEX 3
#define HIGHEST_WINSTREAK_INDEX 4
#define GUESS_DISTRIBUTION_START_INDEX 5
#define GUESS_DISTRIBUTION_END_INDEX 10
namespace model
{
class FileManager
{
public:
    FileManager();
    virtual ~FileManager();
    void loadDictionary(WordleManager* manager);
    void loadUserData(StatisticsManager* manager);
    void loadSettingsData(SettingsManager* manager);
    void saveUserData(StatisticsManager* manager);
    void saveSettingsData(SettingsManager* manager);
};
}
#endif // FILEMANAGER_H
