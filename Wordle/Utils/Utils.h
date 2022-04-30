#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

#define GUESS_LIMIT 6
namespace utils
{
const string toUpperCase(string text);
const string toLowerCase(string text);
int toInt(const string& text, const char* errorMessage);
vector<string> split(string, char);
}
#endif // UTILS_H