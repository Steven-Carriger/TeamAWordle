#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
using namespace std;

#define DEFAULT_USERNAME "guest"
#define EMPTY_CHARACTER " "
#define FLOAT_TO_PERCENT_VALUE 100
namespace model
{
class Player
{
private:
    string userName;
    int totalGames;
    int totalWins;
    int currentWinStreak;
    int highestWinStreak;
    vector<int> guessDistribution;
public:
    Player();
    virtual ~Player();
    int getTotalGames();
    int getTotalWins();
    int getCurrentWinStreak();
    int getHighestWinStreak();
    int getAmountOfGuessesAtIndex(int index);
    const string& getUserName();
    void setUserName(const string& userName);
    void setTotalGames(int numberOfGames);
    void setTotalWins(int numberOfWins);
    void setCurrentWinStreak(int streakNumber);
    void setHighestWinStreak(int highestStreak);
    void setGuessCountAtIndex(int index, int guessCount);
    float calculateWinRate();
};
}
#endif // PLAYER_H
