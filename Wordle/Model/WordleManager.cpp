#include "WordleManager.h"

namespace model
{

/**
* Creates a new Wordle Manager
*/
WordleManager::WordleManager()
{
    srand((int) time(0));
    this->allowRepeatLetters = false;
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
        if (!this->allowRepeatLetters)
        {
            for (int i = 0; i < tmpWord.length(); i++)
            {
                if (count(tmpWord.begin(), tmpWord.end(), tmpWord[i]) > 1)
                {
                    tmpWord = "";
                    break;
                }
            }
        }
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

/**
* Sets the repeated letters to be allowed or not
*
* @param the value to determine if repeated letters are allowed or not
*/
void WordleManager::setRepeatedLetters(bool allowRepeatLetters)
{
    this->allowRepeatLetters = allowRepeatLetters;
}

/**
* Gets if repeated letters are allowed or not
*
* @return true if repeated letters are allowed, false otherwise
*/
bool WordleManager::isRepeatedLettersAllowed()
{
    return this->allowRepeatLetters;
}

}
