#include <iostream>
using namespace std;

union Data {
    int intValue;
    double doubleValue;
    char charValue;
};

int main() {
    Data data;

    data.intValue = 65;

    data.doubleValue = 3.14;

    data.charValue = 'A';
    cout << "intValue: " << data.intValue << endl;
    cout << "doubleValue: " << data.doubleValue << endl;
    cout << "charValue: " << data.charValue << endl;

    data.doubleValue = 2.34;

    data.charValue = 'N';
    cout << "intValue: " << data.intValue << endl;
    cout << "doubleValue: " << data.doubleValue << endl;
    cout << "charValue: " << data.charValue << endl;
    // ВАЖНО: В объединении хранится только одно значение за раз!
    // Присвоение нового значения затирает предыдущее

    return 0;
}