#include "FileManager.h"

namespace model
{

FileManager::FileManager()
{
    //ctor
}

void FileManager::loadDictionary(WordleManager* manager)
{
    const string& dictionaryFile = "dictionary.txt";
    ifstream inputFile (dictionaryFile);
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

void FileManager::loadUserData(StatisticsManager* manager)
{
    ifstream inputFile("userStats.csv");
    string line;
    while ( getline (inputFile,line) )
    {
        Player* user = new Player();
        vector<string> information = split(line, ',');
        const string usersName = information[0];
        int usersTotalGames = toInt(information[1], "Error converting a users total games to an integer.");
        int usersTotalWins = toInt(information[2], "Error converting a users total wins to an integer.");
        int usersWinStreak = toInt(information[3], "Error converting a users win streak to an integer.");
        int usersHighestWinStreak = toInt(information[4], "Error converting a users highest win streak to an integer.");

        for (int index = 5; index < information.size(); index++)
        {
            user->setGuessCountAtIndex(index - 5, toInt(information[index], "Error converting a users highest win streak to an integer."));
        }

        user->setUserName(toLowerCase(usersName));
        user->setTotalGames(usersTotalGames);
        user->setTotalWins(usersTotalWins);
        user->setCurrentWinStreak(usersWinStreak);
        user->setHighestWinStreak(usersHighestWinStreak);
        map<string, Player*>& userStats = manager->getUserStats();
        userStats[usersName] = user;
    }
    inputFile.close();
}

void FileManager::saveUserData(StatisticsManager* manager)
{
    ofstream saveFile;
    saveFile.open("userStats.csv");
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

FileManager::~FileManager()
{
    //dtor
}

}
