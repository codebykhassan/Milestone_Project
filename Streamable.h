// Final Project Milestone 4
// File    Streamable.h
// Version 4.0
// Author    Fardad Soleimanloo
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Khassan Suleimanov  17 Jul,2024
/////////////////////////////////////////////////////////////////
#ifndef SENECA_STREAMABLE_H_
#define SENECA_STREAMABLE_H_
#include <iostream>
namespace seneca {
class Streamable{
public:
    virtual std::ostream& write(std::ostream& os) const = 0;
    virtual std::istream& read(std::istream& is) = 0;
    virtual bool conIO(std::ios& io) const = 0;
    virtual operator bool() const = 0;
    virtual ~Streamable() {};
};
std::ostream& operator << (std::ostream& os, const Streamable& obj);
std::istream& operator >> (std::istream& is, Streamable& obj);







}
#endif
