#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <ctime>

using namespace std;

class Book {
public:
    string title;
    string author;
    string isbn;
    bool is_available;

    Book(string t, string a, string i) : title(t), author(a), isbn(i), is_available(true) {}
};

class Library {
private:
    vector<Book> books;
    unordered_map<string, pair<string, time_t>> transactions; // ISBN -> {Borrower, Due Date}

public:
    void addBook(string title, string author, string isbn) {
        books.emplace_back(title, author, isbn);
        cout << "Successfully added book: " << title << " by " << author << " (ISBN: " << isbn << ")." << endl;
    }

    void searchBooks(string query) {
        bool found = false;
        for (const auto &book : books) {
            if (book.title.find(query) != string::npos || book.author.find(query) != string::npos || book.isbn == query) {
                found = true;
                string status = book.is_available ? "Available" : "Checked out";
                cout << "- Title: " << book.title << ", Author: " << book.author << ", ISBN: " << book.isbn << ", Status: " << status << endl;
            }
        }
        if (!found) {
            cout << "No books match your search query." << endl;
        }
    }

    void checkoutBook(string isbn, string borrower) {
        for (auto &book : books) {
            if (book.isbn == isbn && book.is_available) {
                book.is_available = false;
                time_t now = time(0);
                time_t due_date = now + 14 * 24 * 60 * 60; // 14 days from now
                transactions[isbn] = {borrower, due_date};
                cout << "'" << book.title << "' has been checked out by " << borrower << ". Due back on " << ctime(&due_date);
                return;
            }
        }
        cout << "Unable to checkout book. Either it's not available or the ISBN is incorrect." << endl;
    }

    void returnBook(string isbn) {
        auto it = transactions.find(isbn);
        if (it != transactions.end()) {
            for (auto &book : books) {
                if (book.isbn == isbn) {
                    book.is_available = true;
                    time_t now = time(0);
                    time_t due_date = it->second.second;
                    double overdue_days = difftime(now, due_date) / (24 * 60 * 60);
                    if (overdue_days > 0) {
                        double fine = overdue_days * 2; // $2 per overdue day
                        cout << "Book returned late. Overdue fine: $" << fine << endl;
                    } else {
                        cout << "Book returned on time. No fine charged." << endl;
                    }
                    transactions.erase(it);
                    return;
                }
            }
        }
        cout << "Return failed. No record of this transaction." << endl;
    }

    void displayBooks() {
        if (books.empty()) {
            cout << "The library has no books at the moment." << endl;
            return;
        }
        cout << "Library Books:" << endl;
        for (const auto &book : books) {
            string status = book.is_available ? "Available" : "Checked out";
            cout << "- Title: " << book.title << ", Author: " << book.author << ", ISBN: " << book.isbn << ", Status: " << status << endl;
        }
    }
};

void mainMenu() {
    Library library;
    int choice;

    do {
        cout << "\nLibrary Management System" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Search for Books" << endl;
        cout << "3. Checkout a Book" << endl;
        cout << "4. Return a Book" << endl;
        cout << "5. View All Books" << endl;
        cout << "6. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore(); // Ignore leftover newline

        switch (choice) {
        case 1: {
            string title, author, isbn;
            cout << "Enter book title: ";
            getline(cin, title);
            cout << "Enter book author: ";
            getline(cin, author);
            cout << "Enter book ISBN: ";
            getline(cin, isbn);
            library.addBook(title, author, isbn);
            break;
        }
        case 2: {
            string query;
            cout << "Enter title, author, or ISBN to search: ";
            getline(cin, query);
            library.searchBooks(query);
            break;
        }
        case 3: {
            string isbn, borrower;
            cout << "Enter ISBN of the book to checkout: ";
            getline(cin, isbn);
            cout << "Enter borrower's name: ";
            getline(cin, borrower);
            library.checkoutBook(isbn, borrower);
            break;
        }
        case 4: {
            string isbn;
            cout << "Enter ISBN of the book to return: ";
            getline(cin, isbn);
            library.returnBook(isbn);
            break;
        }
        case 5:
            library.displayBooks();
            break;
        case 6:
            cout << "Thank you for using the Library Management System. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);
}

int main() {
    mainMenu();
    return 0;
}