#ifndef WORDLEMANAGER_H
#define WORDLEMANAGER_H

#include <string>
#include <vector>
using namespace std;

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
public:
    WordleManager();
    virtual ~WordleManager();
    const string& getCurrentWord();
    void randomizeWord(int wordLength);
    bool validateWord(const string& word);
    bool guessWord(const string& word);
    vector<WordleManager::LetterState> getDetails(const string& word);
private:
    void load();
};

};

#endif // WORDLEMANAGER_H
