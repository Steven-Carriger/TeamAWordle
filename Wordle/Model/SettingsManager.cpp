#include "SettingsManager.h"

#define DEFULT_WORD_LENGTH 5

namespace model {

SettingsManager::SettingsManager()
{
    this->repeatsAllowed = false;
    this->wordLength = DEFULT_WORD_LENGTH;
}

SettingsManager::~SettingsManager()
{
    //dtor
}

int SettingsManager::getWordLength() {
    return this->wordLength;
}

bool SettingsManager::isRepeatsAllowed() {
    return this->repeatsAllowed;
}

void SettingsManager::setRepeatsAllowed(bool allowRepeats)
{
    this->repeatsAllowed = allowRepeats;
}

void SettingsManager::setWordLength(int wordLength)
{
    this->wordLength = wordLength;
}

}
