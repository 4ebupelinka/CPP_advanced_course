#include <iostream>
#include <limits> 
using namespace std;

bool readNumber(double& num) {
    cin >> num;
    if (cin.fail()) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка: введите корректное число!" << endl;
        return false;
    }
    return true;
}

bool readOperator(char& op) {
    cin >> op;
    if (op != '+' && op != '-' && op != '*' && op != '/' && op != '=') {
        cout << "Ошибка: недопустимый оператор. Используйте +, -, *, / или =" << endl;
        return false;
    }
    return true;
}

int main() {
    double result = 0;
    double num;
    char op;
    bool firstInput = true;

    cout << "=== Калькулятор как на телефоне ===" << endl;
    cout << "Введите число, затем оператор (+, -, *, /),\n";
    cout << "повторяйте пока не введёте '=' для вывода результата." << endl;

    while (true) {
        // Чтение числа
        cout << "\nВведите число: ";
        while (!readNumber(num)) {
            cout << "Попробуйте снова: ";
        }

        if (firstInput) {
            result = num;
            firstInput = false;
        }
        else {
            switch (op) {
            case '+': result += num; break;
            case '-': result -= num; break;
            case '*': result *= num; break;
            case '/':
                if (num == 0) {
                    cout << "Ошибка: деление на ноль!" << endl;
                    continue;
                }
                result /= num;
                break;
            }
        }

        cout << "Введите оператор (+, -, *, /, =): ";
        while (!readOperator(op)) {
            cout << "Попробуйте снова: ";
        }

        if (op == '=') {
            cout << "\nРезультат: " << result << endl;
            break;
        }
    }

    cout << "\nВыход из программы. До свидания!" << endl;
    return 0;
}
