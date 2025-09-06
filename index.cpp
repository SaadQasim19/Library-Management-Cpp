#include <iostream>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

class Book {
public:
    int id;
    string name;
    string author;
    bool isIssued;
    string issuedTo;

    Book(int bookId, string bookName, string bookAuthor) {
        id = bookId;
        name = bookName;
        author = bookAuthor;
        isIssued = false;
        issuedTo = "";
    }

    void display() {
        cout << "ID: " << id << " | Book: " << name << " | Author: " << author;
        if (isIssued) {
            cout << " | [ISSUED to: " << issuedTo << "]";
        } else {
            cout << " | [AVAILABLE]";
        }
        cout << endl;
    }
};

class Library {
private:
    vector<Book> books;
    string booksFile = "library_books.txt";

    void loadBooksFromFile() {
        ifstream file(booksFile);
        if (file.is_open()) {
            int id;
            string name, author, issuedStatus, issuedTo;
            while (file >> id) {
                file.ignore();
                getline(file, name);
                getline(file, author);
                file >> issuedStatus;
                file.ignore();
                getline(file, issuedTo);

                Book newBook(id, name, author);
                if (issuedStatus == "1") {
                    newBook.isIssued = true;
                    newBook.issuedTo = issuedTo;
                }
                books.push_back(newBook);
            }
            file.close();
        }
    }

    void saveBooksToFile() {
        ofstream file(booksFile);
        if (file.is_open()) {
            for (Book &book : books) {
                file << book.id << endl;
                file << book.name << endl;
                file << book.author << endl;
                file << (book.isIssued ? 1 : 0) << endl;
                file << book.issuedTo << endl;
            }
            file.close();
        }
    }

public:
    Library() {
        loadBooksFromFile();
    }

    ~Library() {
        saveBooksToFile();
    }

    void addBook() {
        int id;
        string name, author;

        cout << "\n--- Add New Book ---" << endl;
        cout << "Enter Book ID: ";
        cin >> id;

        for (Book &book : books) {
            if (book.id == id) {
                cout << "Error! A book with this ID already exists." << endl;
                return;
            }
        }

        cin.ignore();
        cout << "Enter Book Name: ";
        getline(cin, name);
        cout << "Enter Author Name: ";
        getline(cin, author);

        Book newBook(id, name, author);
        books.push_back(newBook);
        cout << "Book added successfully!" << endl;
        saveBooksToFile();
    }

    void displayAllBooks() {
        if (books.empty()) {
            cout << "\nNo books in the library." << endl;
            return;
        }

        cout << "\n--- All Books in Library ---" << endl;
        for (Book &book : books) {
            book.display();
        }
    }

    void searchBook() {
        int searchId;
        cout << "\n--- Search for a Book ---" << endl;
        cout << "Enter Book ID to search: ";
        cin >> searchId;

        for (Book &book : books) {
            if (book.id == searchId) {
                cout << "Book Found!" << endl;
                book.display();
                return;
            }
        }
        cout << "Book with ID " << searchId << " not found." << endl;
    }

    void issueBook() {
        int issueId;
        string studentName;
        cout << "\n--- Issue a Book ---" << endl;
        cout << "Enter Book ID to issue: ";
        cin >> issueId;
        cin.ignore();

        for (Book &book : books) {
            if (book.id == issueId) {
                if (book.isIssued) {
                    cout << "Sorry, this book is already issued to: " << book.issuedTo << endl;
                    return;
                }
                cout << "Enter Student Name: ";
                getline(cin, studentName);
                book.isIssued = true;
                book.issuedTo = studentName;
                cout << "Book issued successfully to " << studentName << "!" << endl;
                saveBooksToFile();
                return;
            }
        }
        cout << "Book with ID " << issueId << " not found." << endl;
    }

    void returnBook() {
        int returnId;
        cout << "\n--- Return a Book ---" << endl;
        cout << "Enter Book ID to return: ";
        cin >> returnId;

        for (Book &book : books) {
            if (book.id == returnId) {
                if (!book.isIssued) {
                    cout << "This book was not issued. It is already available." << endl;
                    return;
                }
                cout << "Book \"" << book.name << "\" returned by " << book.issuedTo << "." << endl;
                book.isIssued = false;
                book.issuedTo = "";
                saveBooksToFile();
                return;
            }
        }
        cout << "Book with ID " << returnId << " not found." << endl;
    }
};

void displayMenu() {
    cout << "\n\n*** Library Management System ***" << endl;
    cout << "1. Add a New Book" << endl;
    cout << "2. Display All Books" << endl;
    cout << "3. Search for a Book" << endl;
    cout << "4. Issue a Book" << endl;
    cout << "5. Return a Book" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice (1-6): ";
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cin >> choice;

       
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                library.addBook();
                break;
            case 2:
                library.displayAllBooks();
                break;
            case 3:
                library.searchBook();
                break;
            case 4:
                library.issueBook();
                break;
            case 5:
                library.returnBook();
                break;
            case 6:
                cout << "Thank you for using the Library Management System. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice! Please select an option between 1-6." << endl;
        }
    } while (choice != 6);

    return 0;
}
