#include "Player.h"

namespace model
{

Player::Player()
{
    this->userName = string("");
    this->totalGames = 0;
    this->totalWins = 0;
    this->currentWinStreak = 0;
    this->highestWinStreak = 0;
    this->guessDistribution = {0, 0, 0, 0, 0, 0};
}

int Player::getTotalGames()
{
    return this->totalGames;
}

int Player::getTotalWins()
{
    return this->totalWins;
}

int Player::getCurrentWinStreak()
{
    return this->currentWinStreak;
}

int Player::getHighestWinStreak()
{
    return this->highestWinStreak;
}

int Player::getAmountOfGuessesAtIndex(int index)
{
    if (this->guessDistribution.size() > index)
    {
        return this->guessDistribution[index];
    }
}

const string& Player::getUserName()
{
    return this->userName;
}

void Player::setTotalGames(int numberOfGames)
{
    this->totalGames = numberOfGames;
}

void Player::setTotalWins(int numberOfWins)
{
    this->totalWins = numberOfWins;
}

void Player::setCurrentWinStreak(int streakNumber)
{
    if (streakNumber > this->highestWinStreak)
    {
        this->setHighestWinStreak(streakNumber);
    }
    this->currentWinStreak = streakNumber;
}

void Player::setHighestWinStreak(int highestStreak)
{
    this->highestWinStreak = highestStreak;
}

void Player::setGuessCountAtIndex(int index, int guessCount)
{
    if (this->guessDistribution.size() > index)
    {
        this->guessDistribution[index] = guessCount;
    }
}

void Player::setUserName(const string& userName)
{
    this->userName = userName;
}

float Player::calculateWinRate()
{
    if (totalGames == 0)
    {
        return 0;
    }
    float rate = (float)this->totalWins / (float)this->totalGames;
    return rate * 100;
}

Player::~Player()
{
    //dtor
}

}
