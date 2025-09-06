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

int main(){

}