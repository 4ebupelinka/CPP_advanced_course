#include <iostream>
using namespace std;

void Task_1();
void Task_2();
void Task_3();
void Task_4();
void Task_5();
void Task_6();
void Task_7();
void Task_8();
void Task_9();
void Task_10();

int main() {
    int choice = 0;
    cout << "Выберите задание (1-10): ";
    cin >> choice;

    switch (choice) {
    case 1:
        Task_1();
        break;
    case 2:
        Task_2();
        break;
    case 3:
        Task_3();
        break;
    case 4:
        Task_4();
        break;
    case 5:
        Task_5();
        break;
    case 6:
        Task_6();
        break;
    case 7:
        Task_7();
        break;
    case 8:
        Task_8();
        break;
    case 9:
        Task_9();
        break;
    case 10:
        Task_10();
        break;
    default:
        cout << "Неверный номер задания." << endl;
        break;
    }

    return 0;
}
