#include "Task_10_sort_and_search.h"
#include <iostream>
#include <string>

struct Book {
    std::string title;
    std::string author;
    int year;
    double price;
};

void printBook(const Book& b) {
    std::cout << "Название: " << b.title << "\n";
    std::cout << "Автор: " << b.author << "\n";
    std::cout << "Год: " << b.year << "\n";
    std::cout << "Цена: " << b.price << "\n";
}

void sortBooksByYear(Book* books, int size) {
    if (books == nullptr || size <= 1) return;

    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (books[j].year > books[j + 1].year) {
                Book temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
}

Book* findBookByAuthor(Book* books, int size, const std::string& author) {
    if (books == nullptr) return nullptr;

    for (int i = 0; i < size; ++i) {
        if (books[i].author == author) {
            return &books[i];  
        }
    }
    return nullptr; 
}

void printAllBooks(const Book* books, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << "Книга #" << (i + 1) << ":\n";
        printBook(books[i]);
        std::cout << "-----------------\n";
    }
}

void RunTask10() {
    int size = 5;
    Book* library = new Book[size]{
        {"Непобедимый", "Станислав Лем", 1963, 1500.0},
        {"Пятьдесят оттенков серого", "Эрика Леонард", 2011, 1700.0},
        {"Мастер и Маргарита", "Михаил Булгаков", 1966, 1300.0},
        {"Эдэм", "Станислав Лем", 1958, 1200.0},
        {"Дуб", "Александр Пушкин", 1833, 1400.0}
    };

    std::cout << "Исходный список книг:\n";
    printAllBooks(library, size);

    sortBooksByYear(library, size);
    std::cout << "\nПосле сортировки по году издания:\n";
    printAllBooks(library, size);

    std::string author = "Станислав Лем";

    Book* found = findBookByAuthor(library, size, author);
    if (found != nullptr) {
        std::cout << "\nКнига автора:" << author <<" найдена:\n";
        printBook(*found);
    }
    else {
        std::cout << "\nКнига автора:" << author << " не найдена:\n";

    }

    delete[] library;
}
