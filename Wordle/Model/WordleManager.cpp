#include "WordleManager.h"

#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

namespace model
{

WordleManager::WordleManager(int wordLength)
{
    this->wordLength = wordLength;
    this->load();
    srand((int) time(0));
}

WordleManager::~WordleManager()
{
    //dtor
}

void WordleManager::load()
{
    const string& dictionaryFile = "dictionary.txt";
    ifstream inputFile (dictionaryFile);
    if (inputFile.is_open())
    {
        string line;
        while ( getline (inputFile,line) )
        {
            line.pop_back();
            this->dictionary.push_back(line);
        }
        inputFile.close();
    }
    else throw runtime_error("Failed to load dictionary.");
}

const string& WordleManager::getCurrentWord()
{
    return this->currentWord;
}

void WordleManager::randomizeWord()
{
    string tmpWord;
    while (tmpWord.length() != this->wordLength)
    {
        int indx = rand() % this->dictionary.size();
        tmpWord = this->dictionary[indx];
    }
    this->currentWord = tmpWord;
}

bool WordleManager::validateWord(const string& word)
{
    if (word.length() == this->wordLength) return false;
    for (auto aWord = this->dictionary.begin(); aWord != this->dictionary.end(); ++aWord)
    {
        if (*aWord == word) return true;
    }
    return false;
}

bool WordleManager::guessWord(const string& word)
{
    return this->currentWord == word;
}

vector<WordleManager::LetterState> WordleManager::getDetails(const string& word)
{
    vector<WordleManager::LetterState> states(this->wordLength);
    string tmpWord(this->currentWord);
    for (int i = 0; i < word.length(); ++i)
    {
        if (word[i] == this->currentWord[i])
        {
            states[i] = LetterState::CORRECT;
            tmpWord = tmpWord.replace(i, 1, " ");
        }
    }

    for (int i = 0; i < word.length(); ++i)
    {
        if (tmpWord.find(word[i]) != string::npos)
        {
            states[i] = WordleManager::LetterState::IN_WORD;
        }
    }
    return states;
}

}
