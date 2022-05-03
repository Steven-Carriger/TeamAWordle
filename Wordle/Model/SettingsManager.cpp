#include "SettingsManager.h"

namespace model {

/**
* Creates a new SettingsManager
*/
SettingsManager::SettingsManager()
{
    this->repeatsAllowed = false;
    this->wordLength = DEFULT_WORD_LENGTH;
}

/**
* SettingsManager deconstructor
*/
SettingsManager::~SettingsManager()
{
    //dtor
}

/**
* Gets the word length that is currently selected
*
* @return the word length
*/
int SettingsManager::getWordLength() {
    return this->wordLength;
}

/**
* Gets the value of whether repeats are allowed or not
*
* @return true if repeats are allowed, false otherwise
*/
bool SettingsManager::isRepeatsAllowed() {
    return this->repeatsAllowed;
}

/**
* Sets the repeats value
*
* @param allowRepeats the value to set the allow repeats to
*/
void SettingsManager::setRepeatsAllowed(bool allowRepeats)
{
    this->repeatsAllowed = allowRepeats;
}

/**
* Sets the word length in the settings
*
* @param wordLength the word length to set the word length to.
*/
void SettingsManager::setWordLength(int wordLength)
{
    this->wordLength = wordLength;
}

}
