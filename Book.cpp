// Final Project Milestone 4
// File    Book.cpp
// Version 4.0
// Author    Fardad Soleimanloo
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Khassan Suleimanov  17 Jul,2024
/////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include <iomanip>
#include "Book.h"

namespace seneca {
Book::Book() : authorName(nullptr){}

Book:: Book(const Book& other) : Book(){
    *this = other;
}
Book& Book::operator=(const Book &other) {
    if (this != &other) {
        Publication::operator=(other);
        delete [] authorName;
        if (other.authorName) {
            authorName = new char[strlen(other.authorName) + 1];
            strcpy(authorName, other.authorName);
        } else {
            authorName = nullptr;
        }
    }
    return *this;
}
Book::~Book(){
    delete [] authorName;
}
char Book::type() const{
    return 'B';
}
std::ostream& Book::write(std::ostream &os) const{
    Publication::write(os);
    if (conIO(os)) {
        os << ' ' << std::left << std::setw(SENECA_AUTHOR_WIDTH) << std::string(authorName).substr(0, SENECA_AUTHOR_WIDTH) << " |";
        } 
        else {
            os << '\t' << authorName;
    }
    return os;
}
std::istream& Book::read(std::istream &is) {
    char tempAuthor[256];
    Publication::read(is);
    if(authorName) delete[]authorName;
    if (conIO(is)) {
        std::cout << "Author: ";
        is.ignore();
        is.getline(tempAuthor, 256);
    } else{
        is.ignore(1, '\t');
        is.get(tempAuthor, 256);
    }
    
    if (!is.fail()) {
        authorName = new char[strlen(tempAuthor) + 1];
        strcpy(authorName, tempAuthor);
    }
    return is;
}

void Book::set(int member_id){
    Publication::set(member_id);
    resetDate();
}

Book::operator bool() const {
    return authorName!= nullptr && authorName[0] != '\0' && Publication::operator bool();
}

}
