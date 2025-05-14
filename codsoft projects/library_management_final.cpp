#include<iostream>
#include<string>
#include<ctime>
using namespace std;

struct Book {
    int bookID;
    string title;
    string author;
    int quantity;
};

struct Borrower {
    int borrowerID;
    string name;
    string contactInfo;
};

struct Transaction {
    int transactionID;
    int bookID;
    int borrowerID;
    time_t checkoutDate;
    time_t dueDate;
    time_t returnDate;
    double fineAmount;
};

// Function Declarations
void addBook(Book library[], int &count);
void displayBooks(const Book library[], int count);
void searchBook(const Book library[], int count);
void updateBook(Book library[], int count);
void deleteBook(Book library[], int &count);

void checkoutBook(Book library[], int &bookCount, Borrower borrowers[], int &borrowerCount, Transaction transactions[], int &transactionCount);
void returnBook(Book library[], int &bookCount, Transaction transactions[], int transactionCount);
void calculateFine(Transaction &transaction);

int main() {
    const int maxBook = 100, maxBorrower = 100, maxTransaction = 100;
    Book library[maxBook];
    Borrower borrowers[maxBorrower];
    Transaction transactions[maxTransaction];

    int bookCount = 0, borrowerCount = 0, transactionCount = 0;
    int choice;

    cout << "===== Welcome to Library Management System =====\n";

    do {
        cout << "\nMenu:\n";
        cout << "1. Add New Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book\n";
        cout << "4. Update Book Information\n";
        cout << "5. Delete Book\n";
        cout << "6. Checkout Book\n";
        cout << "7. Return Book\n";
        cout << "8. Exit\n";

        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(library, bookCount); break;
            case 2: displayBooks(library, bookCount); break;
            case 3: searchBook(library, bookCount); break;
            case 4: updateBook(library, bookCount); break;
            case 5: deleteBook(library, bookCount); break;
            case 6: checkoutBook(library, bookCount, borrowers, borrowerCount, transactions, transactionCount); break;
            case 7: returnBook(library, bookCount, transactions, transactionCount); break;
            case 8: cout << "Exiting the system. Goodbye!\n"; break;
            default: cout << "Invalid choice. Please try again.\n"; break;
        }
    } while (choice != 8);

    return 0;
}

// Function to Add New Book
void addBook(Book library[], int &count) {
    cout << "Enter Book ID: ";
    cin >> library[count].bookID;
    cin.ignore(); // Clears newline after integer input

    cout << "Enter Book Title: ";
    getline(cin, library[count].title);

    cout << "Enter Author Name: ";
    getline(cin, library[count].author);

    cout << "Enter Quantity: ";
    cin >> library[count].quantity;

    cout << "Book Added Successfully!\n";
    count++;
}

// Function to Display All Books
void displayBooks(const Book library[], int count) {
    if (count == 0) {
        cout << "\nNo books available.\n";
        return;
    }

    cout << "\nList of Books:\n";
    for (int i = 0; i < count; i++) {
        cout << "-----------------------------\n";
        cout << "Book ID   : " << library[i].bookID << endl;
        cout << "Title     : " << library[i].title << endl;
        cout << "Author    : " << library[i].author << endl;
        cout << "Quantity  : " << library[i].quantity << endl;
    }
}

// Function to Search Book
void searchBook(const Book library[], int count) {
    int id;
    cout << "Enter Book ID to search: ";
    cin >> id;

    for (int i = 0; i < count; i++) {
        if (library[i].bookID == id) {
            cout << "Book Found!\n";
            cout << "Title    : " << library[i].title << endl;
            cout << "Author   : " << library[i].author << endl;
            cout << "Quantity : " << library[i].quantity << endl;
            return;
        }
    }

    cout << "Book not found.\n";
}

// Function to Update Book
void updateBook(Book library[], int count) {
    int id;
    cout << "Enter Book ID to update: ";
    cin >> id;
    cin.ignore();

    for (int i = 0; i < count; i++) {
        if (library[i].bookID == id) {
            cout << "Enter new Title: ";
            getline(cin, library[i].title);

            cout << "Enter new Author: ";
            getline(cin, library[i].author);

            cout << "Enter new Quantity: ";
            cin >> library[i].quantity;

            cout << "Book Information Updated Successfully!\n";
            return;
        }
    }

    cout << "Book not found.\n";
}

// Function to Delete Book
void deleteBook(Book library[], int &count) {
    int id;
    cout << "Enter Book ID to delete: ";
    cin >> id;

    for (int i = 0; i < count; i++) {
        if (library[i].bookID == id) {
            for (int j = i; j < count - 1; j++) {
                library[j] = library[j + 1];
            }

            count--;
            cout << "Book Deleted Successfully!\n";
            return;
        }
    }

    cout << "Book not found.\n";
}

// Function to Checkout a Book
void checkoutBook(Book library[], int &bookCount, Borrower borrowers[], int &borrowerCount, Transaction transactions[], int &transactionCount) {
    int bookID, borrowerID;
    cout << "Enter Book ID to checkout: ";
    cin >> bookID;
    cout << "Enter Borrower ID: ";
    cin >> borrowerID;

    // Check if book is available
    bool bookFound = false;
    bool bookAvailable = false;
    for (int i = 0; i < bookCount; i++) {
        if (library[i].bookID == bookID) {
            bookFound = true;
            if (library[i].quantity > 0) {
                bookAvailable = true;
                library[i].quantity--;
                break;
            }
        }
    }

    if (!bookFound) {
        cout << "Book not found.\n";
        return;
    }

    if (!bookAvailable) {
        cout << "Book is not available.\n";
        return;
    }

    // Proceed with checkout
    transactions[transactionCount].transactionID = transactionCount + 1;
    transactions[transactionCount].bookID = bookID;
    transactions[transactionCount].borrowerID = borrowerID;
    transactions[transactionCount].checkoutDate = time(0);
    transactions[transactionCount].dueDate = time(0) + 7 * 24 * 60 * 60;  // 7 days from checkout
    transactions[transactionCount].fineAmount = 0.0;

    cout << "Book checked out successfully!\n";
    transactionCount++;
}

// Function to Return Book
void returnBook(Book library[], int &bookCount, Transaction transactions[], int transactionCount) {
    int transactionID;
    cout << "Enter Transaction ID to return the book: ";
    cin >> transactionID;

    bool transactionFound = false;
    for (int i = 0; i < transactionCount; i++) {
        if (transactions[i].transactionID == transactionID) {
            transactionFound = true;
            transactions[i].returnDate = time(0);
            calculateFine(transactions[i]);
            // Return the book
            for (int j = 0; j < bookCount; j++) {
                if (library[j].bookID == transactions[i].bookID) {
                    library[j].quantity++;
                    break;
                }
            }
            cout << "Book returned successfully with a fine of " << transactions[i].fineAmount << " units.\n";
            break;
        }
    }

    if (!transactionFound) {
        cout << "Transaction not found.\n";
    }
}

// Function to Calculate Fine
void calculateFine(Transaction &transaction) {
    double fineRate = 0.5;  // Fine per day
    time_t currentTime = time(0);
    double overdueDays = difftime(currentTime, transaction.dueDate) / (60 * 60 * 24);
    if (overdueDays > 0) {
        transaction.fineAmount = overdueDays * fineRate;
    }
    else {
        transaction.fineAmount = 0;
    }
}