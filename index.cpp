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



int main(){

}