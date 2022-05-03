#ifndef WORDLEMANAGER_H
#define WORDLEMANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
using namespace std;

#include "Utils.h"
using namespace utils;

namespace model
{
class WordleManager
{
public:
    enum LetterState
    {
        NOT_IN_WORD, IN_WORD, CORRECT, UNKNOWN
    };
private:
    vector<string> dictionary;
    string currentWord;
    bool allowRepeatLetters;
public:
    WordleManager();
    virtual ~WordleManager();
    const string& getCurrentWord();
    void randomizeWord(int wordLength);
    bool validateWord(const string& word);
    bool guessWord(const string& word);
    void setRepeatedLetters(bool allowRepeatLetters);
    bool isRepeatedLettersAllowed();
    vector<WordleManager::LetterState> getDetails(const string& word);
    vector<string>& getDictionary();
};
};

#endif // WORDLEMANAGER_H
