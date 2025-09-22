#include "CheckErrors.h"
#include <iostream>
#include <string>

static void printExpr(const std::string& expr) {
    
    std::cout << expr << std::endl;
    for (size_t i = 0; i < expr.size(); ++i) {
        std::cout << "=";
    }
}


static void printExpr(const std::string& expr, int errorIndex) {

    std::cout << expr << std::endl;
    for (size_t i = 0; i < expr.size(); ++i) {
        if (i == static_cast<size_t>(errorIndex)) std::cout << "^";
        else std::cout << "=";
    }
    std::cout << std::endl;
}


static void printError(const std::string& expr, int errorCode, int errorIndex) {
    switch (errorCode) {
    case -1: // скобки
        printExpr(expr, errorIndex);
        std::cout << "Ошибка: некорректные скобки\n";
        break;
    case -2: // токенизация
        printExpr(expr, errorIndex);
        std::cout << "Ошибка: неправильный символ или выражение\n";
        break;
    default:
        std::cout << "Неизвестная ошибка (код " << errorCode << ")\n";
        break;
    }
}


static bool checkParentheses(const std::vector<Token>& tokens, const std::string& expr) {
    int depth = 0;
    int errorIndex = 0;
    for (int i = 0; i < tokens.size(); i++) {
        Token t = tokens[i];
        if (std::holds_alternative<std::string>(t)) {
            const std::string& s = std::get<std::string>(t);
            if (s == "(") {
                ++depth;
                errorIndex = i;
            }
            else if (s == ")") {
                if (depth == 0) {
                    errorIndex = i;
                    printError(expr, -1, errorIndex);
                    return false;
                }
                --depth;
            }
        }
    }

    if (depth != 0) {
        printError(expr, -1, errorIndex);
    }
    return depth == 0;
}


static bool tokenizerError(const std::vector<Token>& tokens, const std::string& expr) {
    if (!tokens.empty() && std::holds_alternative<std::string>(tokens[0])
        && std::get<std::string>(tokens[0]) == "E")
    {
        int idx = std::stoul(std::get<std::string>(tokens[1]));
        printError(expr, -2, idx);
        return false;
    }
    return true;
}


bool checkErrors(const std::vector<Token>& tokens, const std::string& expr) {
    if (!checkParentheses(tokens, expr)) {
        return false;
    }
    if (!tokenizerError(tokens, expr)) {
        return false;
    }
    return true;
}
