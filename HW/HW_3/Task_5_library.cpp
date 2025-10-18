#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Book {
private:
    string title;
    string author;
    string isbn;
    int year;
    bool isAvailable;

public:
    Book(const string& t, const string& a, const string& i, int y)
        : title(t), author(a), isbn(i), year(y), isAvailable(true) {
    }

    string getTitle() const {
        return title;
    }

    string getAuthor() const {
        return author;
    }

    string getIsbn() const {
        return isbn;
    }

    int getYear() const {
        return year;
    }

    bool getIsAvailable() const {
        return isAvailable;
    }

    void setTitle(const string& t) {
        title = t;
    }

    void setAuthor(const string& a) {
        author = a;
    }

    void setIsbn(const string& i) {
        isbn = i;
    }

    void setYear(int y) {
        year = y;
    }

    void borrow() {
        if (isAvailable) {
            isAvailable = false;
            cout << "Книга \"" << title << "\" успешно выдана." << endl;
        }
        else {
            cout << "Книга \"" << title << "\" недоступна." << endl;
        }
    }

    void returnBook() {
        if (!isAvailable) {
            isAvailable = true;
            cout << "Книга \"" << title << "\" возвращена в библиотеку." << endl;
        }
        else {
            cout << "Книга \"" << title << "\" уже находится в библиотеке." << endl;
        }
    }

    void displayInfo() const {
        cout << "Название: " << title << endl;
        cout << "Автор: " << author << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Год издания: " << year << endl;
        cout << "Статус: " << (isAvailable ? "Доступна" : "Выдана") << endl;
    }
};

class Library {
private:
    string name;
    string address;
    vector<Book> books;

public:
    Library(const string& n, const string& addr) : name(n), address(addr) {}

    void addBook(const Book& book) {
        books.push_back(book);
        cout << "Книга \"" << book.getTitle() << "\" добавлена в библиотеку." << endl;
    }

    void removeBook(const string& isbn) {
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].getIsbn() == isbn) {
                cout << "Книга \"" << books[i].getTitle() << "\" удалена." << endl;
                books.erase(books.begin() + i);
                return;
            }
        }
        cout << "Книга с ISBN " << isbn << " не найдена." << endl;
    }

    const Book* findBook(const string& title) const {
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].getTitle() == title) {
                return &books[i];
            }
        }
        return NULL;
    }

    void borrowBook(const string& isbn) {
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].getIsbn() == isbn) {
                books[i].borrow();
                return;
            }
        }
        cout << "Книга с ISBN " << isbn << " не найдена." << endl;
    }

    void returnBook(const string& isbn) {
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].getIsbn() == isbn) {
                books[i].returnBook();
                return;
            }
        }
        cout << "Книга с ISBN " << isbn << " не найдена." << endl;
    }

    void displayAllBooks() const {
        if (books.empty()) {
            cout << "Библиотека пуста." << endl;
            return;
        }
        cout << "Все книги в библиотеке:" << endl;
        for (size_t i = 0; i < books.size(); i++) {
            books[i].displayInfo();
            cout << "------------------------------" << endl;
        }
    }

    void displayAvailableBooks() const {
        bool found = false;
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].getIsAvailable()) {
                books[i].displayInfo();
                cout << "------------------------------" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "Доступных книг нет." << endl;
        }
    }
};

void Task_5() {
    Library library("Городская библиотека", "ул. Ленина, 10");

    Book book1("Война и мир", "Лев Толстой", "12345", 1869);
    Book book2("Преступление и наказание", "Федор Достоевский", "67890", 1866);
    Book book3("Мастер и Маргарита", "Михаил Булгаков", "54321", 1967);

    library.addBook(book1);
    library.addBook(book2);
    library.addBook(book3);

    cout << "==============================" << endl;
    library.displayAllBooks();

    cout << "==============================" << endl;
    library.borrowBook("12345");

    cout << "==============================" << endl;
    cout << "Доступные книги:" << endl;
    library.displayAvailableBooks();

    cout << "==============================" << endl;
    library.returnBook("12345");

    cout << "==============================" << endl;
    library.removeBook("67890");
    library.displayAllBooks();
}
