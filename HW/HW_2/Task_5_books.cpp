#include "Task_5_books.h"
#include <iostream>
#include <string>

struct Book {
    std::string title;
    std::string author;
    int year;
    double price;
};

void inputBooks(Book* books, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << "\nКнига #" << (i + 1) << ":\n";
        std::cout << "Введите название: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, books[i].title);

        std::cout << "Введите автора: ";
        std::getline(std::cin, books[i].author);

        std::cout << "Введите год издания: ";
        std::cin >> books[i].year;

        std::cout << "Введите цену: ";
        std::cin >> books[i].price;
    }
}

void printBooks(const Book* books, int size) {
    std::cout << "\nСписок книг:\n";
    for (int i = 0; i < size; ++i) {
        std::cout << "Книга #" << (i + 1) << ":\n";
        std::cout << "  Название: " << books[i].title << "\n";
        std::cout << "  Автор: " << books[i].author << "\n";
        std::cout << "  Год: " << books[i].year << "\n";
        std::cout << "  Цена: " << books[i].price << "\n";
    }
}

void findMostExpensiveBook(const Book* books, int size) {
    int indexMax = 0;
    double maxPrice = books[0].price;

    for (int i = 1; i < size; ++i) {
        if (books[i].price > maxPrice) {
            maxPrice = books[i].price;
            indexMax = i;
        }
    }

    std::cout << "\nСамая дорогая книга:\n";
    std::cout << "  Название: " << books[indexMax].title << "\n";
    std::cout << "  Автор: " << books[indexMax].author << "\n";
    std::cout << "  Год: " << books[indexMax].year << "\n";
    std::cout << "  Цена: " << books[indexMax].price << "\n";
}

void RunTask5() {
    int n = 0;
    std::cout << "Введите количество книг: ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Библиотека не может пустовать или иметь отрицательное количество книг.\n";
        return;
    }

    Book* library = new Book[n];

    inputBooks(library, n);
    printBooks(library, n);
    findMostExpensiveBook(library, n);

    delete[] library;
}
