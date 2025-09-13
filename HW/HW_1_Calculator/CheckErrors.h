#pragma once
#include <vector>
#include <variant>
#include <utility>
#include <string>
using namespace std;

using Token = variant<double, string>;


bool checkErrors(const vector<Token>& tokens);
