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

}
