#include "WordleManager.h"

#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

#include "Utils.h"

namespace model
{

WordleManager::WordleManager()
{
    srand((int) time(0));
}

WordleManager::~WordleManager()
{
    //dtor
}

const string& WordleManager::getCurrentWord()
{
    return this->currentWord;
}

vector<string>& WordleManager::getDictionary()
{
    return this->dictionary;
}

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

bool WordleManager::validateWord(const string& word)
{
    if (word.length() != this->currentWord.length()) return false;

    for (auto aWord = this->dictionary.begin(); aWord != this->dictionary.end(); ++aWord)
    {
        if (*aWord == toLowerCase(word)) return true;

    }
    return false;
}

bool WordleManager::guessWord(const string& word)
{
    return this->currentWord == toLowerCase(word);
}

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
