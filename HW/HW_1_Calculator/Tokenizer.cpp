#include "Tokenizer.h"
#include <regex>
#include <cctype>
#include <vector>
#include <string>

std::vector<Token> tokenize(const std::string& expression) {

    std::vector<Token> tokens;

    std::regex token_re(R"((\d+(\.\d+)?)|(sin|cos|tan|ctan)|([+\-*/%^()]))");
    std::sregex_iterator begin(expression.begin(), expression.end(), token_re);
    std::sregex_iterator end;

    size_t pos = 0;
    for (std::sregex_iterator it = begin; it != end; ++it) {
        std::smatch m = *it;

        if (m.position() != static_cast<ptrdiff_t>(pos)) {
            tokens.clear();
            tokens.emplace_back("E");
            tokens.emplace_back(std::to_string(pos));
            return tokens;
        }

        std::string token = m.str();
        if (m[1].matched) {
            tokens.emplace_back(std::stod(token));
        }
        else {
            tokens.emplace_back(token);
        }

        pos += token.size();
    }

    if (pos != expression.size()) {
        tokens.clear();
        tokens.emplace_back("E");
        tokens.emplace_back(std::to_string(pos));
        tokens.emplace_back(expression);
    }

    return tokens;
}
