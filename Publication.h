// Final Project Milestone 4
// File    Publication.h
// Version 4.0
// Author    Fardad Soleimanloo
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Khassan Suleimanov  17 Jul,2024
/////////////////////////////////////////////////////////////////
#ifndef SENECA_PUBLICATION_H
#define SENECA_PUBLICATION_H

#include <iostream>
#include <cstring>
#include "Date.h"
#include "Streamable.h"
#include "Lib.h"

namespace seneca {
class Publication : public Streamable {
    char* m_title;
    char m_shelfId[SENECA_SHELF_ID_LEN + 1];
    int m_membership;
    int m_libRef;
    Date m_date;
public:
    Publication();
    Publication(const Publication& src);
    Publication& operator=(const Publication& src);
    virtual ~Publication();
    
    virtual void set(int member_id);
    void setRef(int value);
    void resetDate();
    
    virtual char type()const;
    bool onLoan()const;
    Date checkoutDate()const;
    bool operator==(const char* title)const;
    operator const char* ()const;
    int getRef()const;
    
    bool conIO(std::ios& io)const override;
    std::ostream& write(std::ostream& os) const override;
    std::istream& read(std::istream& istr) override;
    operator bool() const override;
};



}
#endif
