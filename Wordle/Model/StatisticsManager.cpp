#include "StatisticsManager.h"

namespace model
{

StatisticsManager::StatisticsManager(string userName)
{
    this->userStats = map<string, Player*>();
    this->loadUserData();
    this->setCurrentUser(toLowerCase(userName));
}

void StatisticsManager::loadUserData()
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
        this->userStats[usersName] = user;
    }
    inputFile.close();
}

void StatisticsManager::saveUserData()
{
    ofstream saveFile;
    saveFile.open("userStats.csv");
    map<string, Player*>::iterator it;

    for (it = this->userStats.begin(); it != userStats.end(); it++)
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

Player* StatisticsManager::getCurrentPlayer()
{
    return this->currentPlayer;
}

void StatisticsManager::setCurrentUser(string userName)
{
    if (!this->userStats.count(userName))
    {
        this->currentPlayer = new Player();
        this->currentPlayer->setUserName(userName);
        this->userStats[userName] = this->currentPlayer;
        cout << this->userStats.size() << endl;
        return;
    }
    this->currentPlayer = this->userStats[userName];
}

StatisticsManager::~StatisticsManager()
{
    //dtor
}

}
