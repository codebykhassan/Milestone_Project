// Final Project Milestone 4
// File    Streamable.cpp
// Version 4.0
// Author    Fardad Soleimanloo
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Khassan Suleimanov  17 Jul,2024
/////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include "Streamable.h"
using namespace std;
namespace seneca {
std::ostream& operator <<(std::ostream& os, const Streamable& obj) {
    if (obj) {
        obj.write(os);
    }
    return os;
}
std::istream& operator >>(std::istream& is, Streamable& obj){
    return obj.read(is);
}
}
