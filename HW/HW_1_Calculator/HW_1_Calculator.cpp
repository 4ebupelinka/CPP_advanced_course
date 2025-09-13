#include <iostream>
#include "Tokenizer.h"
#include "CheckErrors.h"
using namespace std;



int main() {
    string inputString, expr;
    while (true) {
        cout << "Введите выражение: ";
        getline(cin, inputString);
        expr.clear();
            

        for (char c : inputString) if (!isspace(static_cast<unsigned char>(c))) expr.push_back(c);
        auto tokens = tokenize(expr);



        if (!checkErrors(tokens)) {
            continue;
        }

        for (auto& t : tokens) {
            if (holds_alternative<double>(t)) {
                cout << get<double>(t) << " ";
            }
            else {
                cout << get<string>(t) << " ";
            }
        }
        cout << endl;
    } 
    return 0;
}
