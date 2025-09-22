#pragma once
#include <vector>
#include <variant>
#include <string>

using Token = std::variant<double, std::string>;

bool checkErrors(const std::vector<Token>& tokens, const std::string& expr);
