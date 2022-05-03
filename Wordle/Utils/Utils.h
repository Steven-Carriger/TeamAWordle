#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#define GUESS_LIMIT 6
#define EMPTY_STRING " "
namespace utils
{
const string toUpperCase(string text);
const string toLowerCase(string text);
int toInt(const string& text, const char* errorMessage);
bool toBool(const string& test);
vector<string> split(string, char);
}
#endif // UTILS_H
