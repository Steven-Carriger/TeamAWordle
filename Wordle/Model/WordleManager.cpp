#include "WordleManager.h"

#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

#include "Utils.h"

namespace model
{

/**
* Creates a new Wordle Manager
*/
WordleManager::WordleManager()
{
    srand((int) time(0));
}

/**
* Deconstructs the Wordle Manager
*/
WordleManager::~WordleManager()
{
    //dtor
}

/**
* Gets the current word
*
* @return the current word
*/
const string& WordleManager::getCurrentWord()
{
    return this->currentWord;
}

/**
* gets the WordleManager's dictionary
*
* @return the dictionary the WordleManager is using
*/
vector<string>& WordleManager::getDictionary()
{
    return this->dictionary;
}

/**
* Assigns the current word based on the provided word length
*
* @param wordLength the length of the word to determine the generated word
*/
void WordleManager::randomizeWord(int wordLength)
{
    string tmpWord;
    while (tmpWord.length() != wordLength)
    {
        int indx = rand() % this->dictionary.size();
        tmpWord = this->dictionary[indx];
    }
    this->currentWord = tmpWord;
    cout << this->currentWord << endl;
}

/**
* Checks if the provided word is in the WordleManager's dictionary
*
* @param word the word to check
*
* @return true if the word is in the dictionary, false otherwise
*/
bool WordleManager::validateWord(const string& word)
{
    if (word.length() != this->currentWord.length()) return false;

    for (auto aWord = this->dictionary.begin(); aWord != this->dictionary.end(); ++aWord)
    {
        if (*aWord == toLowerCase(word)) return true;

    }
    return false;
}

/**
* Checks if the word is the current word being used
*
* @param word the word to compare to the current word being used
*
* @return true if the word does match, false otherwise
*/
bool WordleManager::guessWord(const string& word)
{
    return this->currentWord == toLowerCase(word);
}

/**
* Gets the details based on the provided word
*
* @param word the word to check through and evaluate
*
* @return the letterStates of the provided word
*/
vector<WordleManager::LetterState> WordleManager::getDetails(const string& word)
{
    vector<WordleManager::LetterState> states(this->currentWord.length());
    for (int i = 0; i < word.length(); ++i)
    {
        if (this->currentWord.find(tolower(word[i])) != string::npos)
        {
            states[i] = WordleManager::LetterState::IN_WORD;
        }
    }

    for (int i = 0; i < word.length(); ++i)
    {

        if (tolower(word[i]) == this->currentWord[i])
        {
            states[i] = LetterState::CORRECT;
        }
    }

    return states;
}

}
