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
