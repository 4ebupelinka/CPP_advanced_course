#pragma once
#include <string>
#include <variant>
#include <vector>

using Token = std::variant<double, std::string>;

std::vector<Token> tokenize(const std::string& expression);
