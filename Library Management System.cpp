#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Book {
private:
    int bookId;
    string title;
    string author;
    bool issued;

public:

    // Add book
    void addBook() {
        cout << "\nEnter Book ID: ";
        cin >> bookId;

        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        issued = false;

        cout << "\nBook added successfully!\n";
    }

    // Display book
    void displayBook() {
        cout << "\n-----------------------------";
        cout << "\nBook ID   : " << bookId;
        cout << "\nTitle     : " << title;
        cout << "\nAuthor    : " << author;
        cout << "\nStatus    : " << (issued ? "Issued" : "Available");
        cout << "\n-----------------------------\n";
    }

    // Search by title or author
    bool search(string keyword) {
        return title.find(keyword) != string::npos ||
               author.find(keyword) != string::npos;
    }

    // Issue book
    bool issueBook() {
        if (issued) {
            return false;
        }

        issued = true;
        return true;
    }

    // Return book
    bool returnBook() {
        if (!issued) {
            return false;
        }

        issued = false;
        return true;
    }

    int getBookId() {
        return bookId;
    }

    bool isIssued() {
        return issued;
    }
};

// Add a new book
void addNewBook() {
    Book b;

    ofstream file("library.dat", ios::binary | ios::app);

    if (!file) {
        cout << "\nError opening file!\n";
        return;
    }

    b.addBook();

    file.write((char*)&b, sizeof(b));

    file.close();
}

// Display all books
void displayBooks() {
    Book b;

    ifstream file("library.dat", ios::binary);

    if (!file) {
        cout << "\nNo books found!\n";
        return;
    }

    bool found = false;

    while (file.read((char*)&b, sizeof(b))) {
        b.displayBook();
        found = true;
    }

    file.close();

    if (!found) {
        cout << "\nNo books available!\n";
    }
}

// Search book
void searchBook() {
    Book b;
    string keyword;
    bool found = false;

    cin.ignore();

    cout << "\nEnter title or author to search: ";
    getline(cin, keyword);

    ifstream file("library.dat", ios::binary);

    while (file.read((char*)&b, sizeof(b))) {

        if (b.search(keyword)) {
            b.displayBook();
            found = true;
        }
    }

    file.close();

    if (!found) {
        cout << "\nBook not found!\n";
    }
}

// Issue book
void issueBook() {
    Book b;
    int id;
    bool found = false;

    cout << "\nEnter Book ID to issue: ";
    cin >> id;

    fstream file("library.dat", ios::binary | ios::in | ios::out);

    if (!file) {
        cout << "\nNo books found!\n";
        return;
    }

    while (file.read((char*)&b, sizeof(b))) {

        if (b.getBookId() == id) {

            found = true;

            if (b.isIssued()) {
                cout << "\nBook is already issued!\n";
            }
            else {
                b.issueBook();

                file.seekp(-static_cast<int>(sizeof(b)), ios::cur);
                file.write((char*)&b, sizeof(b));

                cout << "\nBook issued successfully!\n";
            }

            break;
        }
    }

    file.close();

    if (!found) {
        cout << "\nBook not found!\n";
    }
}

// Return book
void returnBook() {
    Book b;
    int id;
    bool found = false;

    cout << "\nEnter Book ID to return: ";
    cin >> id;

    fstream file("library.dat", ios::binary | ios::in | ios::out);

    if (!file) {
        cout << "\nNo books found!\n";
        return;
    }

    while (file.read((char*)&b, sizeof(b))) {

        if (b.getBookId() == id) {

            found = true;

            if (!b.isIssued()) {
                cout << "\nBook is already available!\n";
            }
            else {
                b.returnBook();

                file.seekp(-static_cast<int>(sizeof(b)), ios::cur);
                file.write((char*)&b, sizeof(b));

                cout << "\nBook returned successfully!\n";
            }

            break;
        }
    }

    file.close();

    if (!found) {
        cout << "\nBook not found!\n";
    }
}

// Main function
int main() {

    int choice;

    do {
        cout << "\n\n======================================";
        cout << "\n       LIBRARY MANAGEMENT SYSTEM";
        cout << "\n======================================";
        cout << "\n1. Add Book";
        cout << "\n2. Display All Books";
        cout << "\n3. Search Book";
        cout << "\n4. Issue Book";
        cout << "\n5. Return Book";
        cout << "\n6. Exit";
        cout << "\n======================================";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            addNewBook();
            break;

        case 2:
            displayBooks();
            break;

        case 3:
            searchBook();
            break;

        case 4:
            issueBook();
            break;

        case 5:
            returnBook();
            break;

        case 6:
            cout << "\nThank you for using Library Management System!\n";
            break;

        default:
            cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}
