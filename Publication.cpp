// Final Project Milestone 4
// File    Publication.cpp
// Version 4.0
// Author    Fardad Soleimanloo
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Khassan Suleimanov  17 Jul,2024
/////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include "Publication.h"
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;
namespace seneca {
Publication::Publication() : m_title(nullptr), m_membership(0), m_libRef(-1) {
    m_shelfId[0] = '\0';
}
Publication::Publication(const Publication& src): Publication(){
    *this = src;
}
Publication& Publication::operator = (const Publication& src){
    if (this != &src) {
        delete[] m_title;
        m_title = nullptr;
        if (src.m_title) {
            m_title = new char[strlen(src.m_title) + 1];
            strcpy(m_title, src.m_title);
        }
        strcpy(m_shelfId, src.m_shelfId);
        m_membership = src.m_membership;
        m_libRef = src.m_libRef;
        m_date = src.m_date;
    }
    return *this;
}
Publication::~Publication(){
    delete[] m_title;
}
void Publication::set(int member_id){
    if ( member_id >= 10000 && member_id <= 99999){
        m_membership = member_id;
    }else{
        m_membership = 0;
    }
}
void Publication::setRef(int value){
    m_libRef = value;
}
void Publication::resetDate(){
    m_date = Date();
}
char Publication::type() const{
    return 'P';
}
bool Publication::onLoan()const{
    return m_membership != 0;
}
Date Publication::checkoutDate() const{
    return m_date;
}
bool Publication::operator==(const char* title) const{
    return strstr(m_title, title) != nullptr;
}
Publication::operator const char *() const{
    return m_title;
}
int Publication::getRef() const{
    return m_libRef;
}
bool Publication::conIO(std::ios &io) const{
    return &io == &std::cin || &io == &std::cout;
}
std::ostream& Publication::write(std::ostream &os) const{
    if (conIO(os)) {
        os << "| " << left << m_shelfId << " | "
            << left << setw(SENECA_TITLE_WIDTH) << setfill('.')
            << string(m_title ? m_title : "N/A").substr(0, SENECA_TITLE_WIDTH) << " | " << setfill(' ');
        if (m_membership != 0) {
            os << m_membership;
        } else{
            os << " N/A ";
        }
        os << " | "
            << left << m_date << " |";
    } else{
        os << type() << '\t' << m_libRef << '\t' << m_shelfId << '\t' << (m_title ? m_title : "N / A") << "\t";
//        if (m_membership != 0) {
//            os << m_membership;
//        } else{
//            os << " N/A ";
//        }
        os << m_membership;
        os << "\t" << m_date;
    }
    return os;
}
std::istream& Publication::read(std::istream &istr){
    char temp_Title[128];
    char temp_ShelfId[5];
    int temp_Membership = 0;
    int temp_LibRef = 0;
    Date temp_date;
    
    delete[] m_title;
    m_title = nullptr;
    m_shelfId[0] = '\0';
    m_membership = 0;
    m_libRef = -1;
    m_date = temp_date;
    
    if (conIO(istr)) {
        cout << "Shelf No: ";
        istr.getline(temp_ShelfId, SENECA_SHELF_ID_LEN + 1);
        if (strlen(temp_ShelfId) != SENECA_SHELF_ID_LEN) {
            istr.setstate(std::ios::failbit);
            return istr;
        }
        cout << "Title: ";
        istr.getline(temp_Title, 128);
        
        cout <<"Date: ";
        istr >> temp_date;
        
        if (!temp_date) {
            istr.setstate(std::ios::failbit);
            return istr;
        }
    }else {
        istr >> temp_LibRef;
        istr.ignore();
        istr.getline(temp_ShelfId, SENECA_SHELF_ID_LEN + 1, '\t');
        istr.getline(temp_Title, 128, '\t');
        istr >> temp_Membership;;
        istr.ignore();
        istr >> temp_date;
        
        if (!temp_date) {
            istr.setstate(std::ios::failbit);
            return istr;
        }
    }
    if (istr) {
        m_title = new char[strlen(temp_Title) + 1];
        strcpy(m_title, temp_Title);
        strcpy(m_shelfId, temp_ShelfId);
        m_membership = temp_Membership;
        m_date = temp_date;
        m_libRef = temp_LibRef;
    }
    return istr;
}
Publication::operator bool() const {
    return (m_title && m_title[0] != '\0') && (m_shelfId[0] != '\0');
}


}

