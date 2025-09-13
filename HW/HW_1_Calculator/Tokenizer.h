#pragma once
#include <string>
#include <variant>
#include <vector>
using namespace std;

using Token = variant<double, string>;

vector<Token> tokenize(const string& expression);
