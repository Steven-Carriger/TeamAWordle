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
