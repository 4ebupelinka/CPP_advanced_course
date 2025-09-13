#include "CheckErrors.h"
#include <string>
#include <iostream>


void printExpr(const vector<Token>& tokens, int errorIndex) {
    for (auto& t : tokens) {
        if (holds_alternative<double>(t)) {
            cout << get<double>(t);
        }
        else {
            cout << get<string>(t);
        }
    }
    cout << endl;
    if (errorIndex != -1) {
        for (size_t i = 0; i < tokens.size(); ++i) {
            if (i == errorIndex) cout << "^";
            else cout << "=";
        }
        cout << endl;
    }
}


void printError(const vector<Token>& tokens, int errorCode, int errorIndex) {
    switch (errorCode) {
    case -1: // скобки
        printExpr(tokens, errorIndex);
        cout << "Ошибка: некорректные скобки\n";
        break;
    case -2: // Токенизация
        printExpr(tokens, errorIndex);
        cout << "Ошибка: неправильный символ или выражение:\n";
        break;
    default:
        cout << "Неизвестная ошибка (код " << errorCode << ")\n";
        break;
    }
}


static bool checkParentheses(const vector<Token>& tokens) {
    int depth = 0; 

    for (const auto& t : tokens) {
        if (holds_alternative<string>(t)) {
            const string& s = get<string>(t);
            if (s == "(") {
                depth++;
            }
            else if (s == ")") {
                if (depth == 0) {
                    return false;
                }
                depth--;
            }
        }
    }
    if (depth != 0) printError(tokens, -1, -1);
    return depth == 0;
}


static bool tokenizerError(const vector<Token>& tokens) {
    if (!tokens.empty() && holds_alternative<string>(tokens[0])
        && get<string>(tokens[0]) == "E")
    {
        int idx = stoul(get<string>(tokens[1]));
        printError(tokens, -2, stoul(get<string>(tokens[1])));
        return false;
    }
}


bool checkErrors(const vector<Token>& tokens) {
    if (!checkParentheses(tokens)) {
        return false;
    }
    return true;
}
