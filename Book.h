// Final Project Milestone 4
// File    Book.h
// Version 4.0
// Author    Fardad Soleimanloo
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Khassan Suleimanov  17 Jul,2024
/////////////////////////////////////////////////////////////////
#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include "Publication.h"
#include "Lib.h"

namespace seneca {
class Book : public Publication {
    char* authorName;
public:
    Book();
    Book(const Book& other);
    Book& operator = (const Book& other);
    ~Book();
    
    char type() const override;
    std::ostream& write(std::ostream& os) const override;
    std::istream& read(std::istream& is) override;
    void set(int member_id) override;
    
    operator bool() const override;
};

}
#endif
