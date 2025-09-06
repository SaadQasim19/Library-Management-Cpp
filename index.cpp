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

        // Check if ID already exists
        for (Book &book : books) {
            if (book.id == id) {
                cout << "Error! A book with this ID already exists." << endl;
                return;
            }
        }

        cin.ignore(); // Clear input buffer
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

int main(){

}