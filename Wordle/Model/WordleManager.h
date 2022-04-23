#ifndef WORDLEMANAGER_H
#define WORDLEMANAGER_H

#include <string>
#include <vector>
using namespace std;

namespace model
{

class WordleManager
{
private:
    int wordLength;
    vector<string> dictionary;
    string currentWord;
public:
    WordleManager(int wordLength);
    virtual ~WordleManager();
    const string& getCurrentWord();
    void randomizeWord();
    void validateWord(const string& word);
    void guessWord(const string& word);
private:
    void load();
};

};

#endif // WORDLEMANAGER_H
