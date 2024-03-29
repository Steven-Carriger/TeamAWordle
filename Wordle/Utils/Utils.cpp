#include "Utils.h"

namespace utils
{

/**
* Converts the provided string to all upper case
*
* @param text the string to convert
*
* @return the word in all upper case
*/
const string toUpperCase(string text)
{
    transform(text.begin(), text.end(), text.begin(), ::toupper);
    return text;
}

/**
* std::string split implementation by using delimiter as a character.
*
* @param strToSplit the string to split
* @param delimeter the delimiter to split the string by
*
* @return the string split up by the delimiter
*/
vector<string> split(string strToSplit, char delimeter)
{
    stringstream ss(strToSplit);
    string item;
    vector<string> splittedStrings;
    while (getline(ss, item, delimeter))
    {
        if (item != EMPTY_STRING)
        {
            splittedStrings.push_back(item);
        }
    }
    return splittedStrings;
}

/** Converts passed in string to an int
*
* @precondition none
* @postcondition none
* @throws Exception if text cannot be converted to an int
*
* @param text text to convert to an int
* @param errorMessage message thrown if a problem occurs when converting text to an int
*
* @return text converted to an int
*/
int toInt(const string& text, const char* errorMessage)
{
    istringstream streamConversion(text);
    int value = 0;
    if (!(streamConversion >> value))
    {
        throw errorMessage;
    }
    return value;
}


/** Converts passed in string to a bool
*
* @precondition none
* @postcondition none
* @throws Exception if text cannot be converted to a bool
*
* @param text text to convert to a bool
*
* @return text converted to an bool
*/
bool toBool(const string& text)
{
    return (bool) toInt(text, "must be 0 or 1");
}

/**
* Converts the provided string to all lower case
*
* @param text the string to convert
*
* @return the word in all lower case
*/
const string toLowerCase(string text)
{
    transform(text.begin(), text.end(), text.begin(), ::tolower);
    return text;
}
}
