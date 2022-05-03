#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#define DEFULT_WORD_LENGTH 5
namespace model {

class SettingsManager
{
    private:
        bool repeatsAllowed;
        int wordLength;
    public:
        SettingsManager();
        virtual ~SettingsManager();
        void setRepeatsAllowed(bool allowRepeats);
        bool isRepeatsAllowed();
        void setWordLength(int wordLength);
        int getWordLength();

};

};

#endif // SETTINGSMANAGER_H
