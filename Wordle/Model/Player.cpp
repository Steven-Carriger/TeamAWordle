#include "Player.h"

namespace model
{

/**
* Creates a new Player Object
*/
Player::Player()
{
    this->userName = string(EMPTY_CHARACTER);
    this->totalGames = 0;
    this->totalWins = 0;
    this->currentWinStreak = 0;
    this->highestWinStreak = 0;
    this->guessDistribution = {0, 0, 0, 0, 0, 0};
}

/**
* gets the total games of the player
*
* @return the total games the player has played
*/
int Player::getTotalGames()
{
    return this->totalGames;
}

/**
* gets the amount of times the player has won
*
* @return the total amount of wins for the player
*/
int Player::getTotalWins()
{
    return this->totalWins;
}

/**
* Gets the player's current win streak
*
* @return the player's current win streak
*/
int Player::getCurrentWinStreak()
{
    return this->currentWinStreak;
}

/**
* gets the player's highest win streak
*
* @return the player's highest win streak
*/
int Player::getHighestWinStreak()
{
    return this->highestWinStreak;
}

/**
* gets the amount of guesses the player has won based on the given index
*
* @param index: the index to check how many times the player won on that guess
*
* @return the amount of guesses that player won on
*/
int Player::getAmountOfGuessesAtIndex(int index)
{
    if (this->guessDistribution.size() > index)
    {
        return this->guessDistribution[index];
    }
}

/**
* gets the player's user name
*
* @return the player's user name
*/
const string& Player::getUserName()
{
    return this->userName;
}

/**
* sets the player's total amount of games
*
* @param numberOfGames the amount of games the player has played
*/
void Player::setTotalGames(int numberOfGames)
{
    this->totalGames = numberOfGames;
}

/**
* sets the player's total wins
*
* @param numberOfWins the player's total wins
*/
void Player::setTotalWins(int numberOfWins)
{
    this->totalWins = numberOfWins;
}

/**
* sets the player's current win streak
*
* @param streakNumber the player's current win streak
*/
void Player::setCurrentWinStreak(int streakNumber)
{
    if (streakNumber > this->highestWinStreak)
    {
        this->setHighestWinStreak(streakNumber);
    }
    this->currentWinStreak = streakNumber;
}

/**
* sets the player's highest win streak
*
* @param highestStreak the player's highest win streak
*/
void Player::setHighestWinStreak(int highestStreak)
{
    this->highestWinStreak = highestStreak;
}

/**
* sets the player's guess count at the specified index
*
* @param index the index to add the guess count
* @param guessCount the amount of times the player has guessed
*/
void Player::setGuessCountAtIndex(int index, int guessCount)
{
    if (this->guessDistribution.size() > index)
    {
        this->guessDistribution[index] = guessCount;
    }
}

/**
* sets the player's user name
*
* @param user name the player's user name
*/
void Player::setUserName(const string& userName)
{
    if (userName.find_first_not_of(EMPTY_CHARACTER) == std::string::npos)
    {
        this->userName = DEFAULT_USERNAME;
        return;
    }
    this->userName = userName;
}

/**
* calculates the player's win rate
*
* @return the player's win rate
*/
float Player::calculateWinRate()
{
    if (totalGames == 0)
    {
        return 0;
    }
    float rate = (float)this->totalWins / (float)this->totalGames;
    return rate * FLOAT_TO_PERCENT_VALUE;
}

/**
* this is a Player deconstructor
*/
Player::~Player()
{
    //dtor
}

}
