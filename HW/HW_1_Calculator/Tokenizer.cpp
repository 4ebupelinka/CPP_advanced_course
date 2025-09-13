#include "Tokenizer.h"
#include <regex>
#include <cctype>

vector<Token> tokenize(const string& expression) {
    vector<Token> tokens;

    regex token_re(R"((\d+(\.\d+)?)|(sin|cos|tan|ctan)|([+\-*/%^()]))");
    auto begin = sregex_iterator(expression.begin(), expression.end(), token_re);
    auto end = sregex_iterator();

    size_t pos = 0;
    for (auto it = begin; it != end; ++it) {
        smatch m = *it;

        if (m.position() != static_cast<ptrdiff_t>(pos)) {
            tokens.clear();
            tokens.emplace_back("E");
            tokens.emplace_back(to_string(pos));
            return tokens;
        }

        string token = m.str();
        if (m[1].matched) {
            tokens.emplace_back(stod(token));
        }
        else {
            tokens.emplace_back(token);
        }

        pos += token.size();
    }

    if (pos != expression.size()) {
        tokens.clear();
        tokens.emplace_back("E");
        tokens.emplace_back(to_string(pos));
    }

    return tokens;
}
