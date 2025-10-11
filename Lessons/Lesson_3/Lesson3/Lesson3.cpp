#include <iostream>
using namespace std;

void memoryHierarchy() {
    // 1. Статическая память (stack)
    int stack_var = 10;
    int* stack_ptr = &stack_var;
    int& stack_link = stack_var;
    int** a = &stack_ptr;
    int*** b = &a;

    // 2. Динамическая память (heap)
    int* heap_ptr = new int(20);

    cout << "Stack variable: " << stack_var << endl;
    cout << "Stack pointer: " << stack_ptr << endl;
    cout << "Stack link: " << stack_link << endl;
    cout << "Heap value: " << *heap_ptr << endl;
    cout << "Stack value: " << ***b << endl;
    ***b = 30;
    cout << "New Stack value: " << stack_var << endl;


    cout << "Heap pointer: " << heap_ptr << endl;

    // 🔍 Вопрос: В чем разница между stack и heap?
    // - Stack: автоматическое управление, быстрый доступ, ограниченный размер
    // - Heap: ручное управление, медленнее, большой размер

    // ОБЯЗАТЕЛЬНО освобождаем динамическую память!
    delete heap_ptr;
    heap_ptr = nullptr;  // Хорошая практика

    // ❌ ОПАСНО: использование после delete
    // cout << *heap_ptr << endl;  // НЕОПРЕДЕЛЕННОЕ ПОВЕДЕНИЕ!
}
int main()
{
    memoryHierarchy();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
