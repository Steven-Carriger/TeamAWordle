#include "FileManager.h"

namespace model
{

/**
* Creates a new File Manager object
*/
FileManager::FileManager()
{
    //ctor
}

/**
* Loads the dictionary for the provided WordleManager
*
* @param manager: the WordleManager to provide the words to
*/
void FileManager::loadDictionary(WordleManager* manager)
{
    ifstream inputFile (DICTIONARY_FILEPATH);
    if (inputFile.is_open())
    {
        string line;
        while ( getline (inputFile,line) )
        {
            line.pop_back();
            manager->getDictionary().push_back(line);
        }
        inputFile.close();
    }
    else throw runtime_error("Failed to load dictionary.");
}

/**
* Loads all of the user data for the specified StatisticsManager
*
* @param manager: the StatisticsManager to provide the data to
*/
void FileManager::loadUserData(StatisticsManager* manager)
{
    ifstream inputFile(USER_STATISTICS_FILEPATH);
    string line;
    while ( getline (inputFile,line) )
    {
        Player* user = new Player();
        vector<string> information = split(line, ',');
        const string usersName = information[USERNAME_INDEX];
        int usersTotalGames = toInt(information[TOTAL_GAMES_INDEX], STRING_CONVERSION_ERROR);
        int usersTotalWins = toInt(information[TOTAL_WINS_INDEX], STRING_CONVERSION_ERROR);
        int usersWinStreak = toInt(information[WINSTREAK_INDEX], STRING_CONVERSION_ERROR);
        int usersHighestWinStreak = toInt(information[HIGHEST_WINSTREAK_INDEX], STRING_CONVERSION_ERROR);

        for (int index = GUESS_DISTRIBUTION_START_INDEX; index < GUESS_DISTRIBUTION_END_INDEX; index++)
        {
            user->setGuessCountAtIndex(index - GUESS_DISTRIBUTION_START_INDEX, toInt(information[index], STRING_CONVERSION_ERROR));
        }

        user->setUserName(toLowerCase(usersName));
        user->setTotalGames(usersTotalGames);
        user->setTotalWins(usersTotalWins);
        user->setCurrentWinStreak(usersWinStreak);
        user->setHighestWinStreak(usersHighestWinStreak);
        map<string, Player*>& userStats = manager->getUserStats();
        userStats[toLowerCase(user->getUserName())] = user;
    }
    inputFile.close();
}

/**
* Saves the specified StatisticsManager's information to a file
*
* @param manager: the StatisticsManager to extract the information from
*/
void FileManager::saveUserData(StatisticsManager* manager)
{
    ofstream saveFile;
    saveFile.open(USER_STATISTICS_FILEPATH);
    map<string, Player*>::iterator it;
    map<string, Player*> userStats = manager->getUserStats();
    for (it = userStats.begin(); it != userStats.end(); it++)
    {
        Player* currentUser = it->second;
        saveFile << currentUser->getUserName() << ",";
        saveFile << to_string(currentUser->getTotalGames()) << ",";
        saveFile << to_string(currentUser->getTotalWins()) << ",";
        saveFile << to_string(currentUser->getCurrentWinStreak()) << ",";
        saveFile << to_string(currentUser->getHighestWinStreak()) << ",";
        for (int index = 0; index < GUESS_LIMIT; index++)
        {
            if (index == GUESS_LIMIT - 1)
            {
                saveFile << to_string(currentUser->getAmountOfGuessesAtIndex(index)) << endl;

            }
            else
            {
                saveFile << to_string(currentUser->getAmountOfGuessesAtIndex(index)) << ",";
            }
        }
    }
    saveFile.close();
}

/**
* This is a deconstructor for the FileManager
*/
FileManager::~FileManager()
{
    //dtor
}

}
