#include "Utils.h"

#include <algorithm>
using namespace std;

const string toUpperCase(string text)
{
    transform(text.begin(), text.end(), text.begin(), ::toupper);
    return text;
}

const string toLowerCase(string text)
{
    transform(text.begin(), text.end(), text.begin(), ::tolower);
    return text;
}
