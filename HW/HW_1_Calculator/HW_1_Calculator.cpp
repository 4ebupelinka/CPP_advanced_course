#include <iostream>
#include <string>
#include <cctype>
#include <variant>
#include "Tokenizer.h"
#include "CheckErrors.h"

int main() {
    std::string inputString, expr;

    while (true) {
        expr.clear();

        std::cout << "Введите выражение: ";
        std::getline(std::cin, inputString);

        for (char c : inputString) {
            if (!std::isspace(static_cast<unsigned char>(c))) {
                expr.push_back(c);
            }
        }

        std::vector<Token> tokens = tokenize(expr);

        if (!checkErrors(tokens, expr)) {
            continue;
        }

        for (const Token& t : tokens) {
            if (std::holds_alternative<double>(t)) {
                std::cout << std::get<double>(t) << " ";
            }
            else {
                std::cout << std::get<std::string>(t) << " ";
            }
        }
        std::cout << std::endl;
    }

    return 0;
}
