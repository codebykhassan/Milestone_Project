/***********************************************************************
// OOP244 Menu Module
// File    Menu.cpp
// Version 2
// Date 7 Jul, 2024
// Author Khassan Suleimanov
// Description
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
//
/////////////////////////////////////////////////////////////////
***********************************************************************/

#ifndef SENECA_LIBAPP_H
#define SENECA_LIBAPP_H
#include "Menu.h"
#include "Publication.h"
namespace seneca {
   class LibApp {
       bool m_changed;
       Menu m_mainMenu;
       Menu m_exitMenu;
       Menu m_typeMenu;
       char m_fileName[256];
       Publication* PPA[SENECA_LIBRARY_CAPACITY];
       int NOLP;
       int LLRN;
       bool confirm(const char* message);
       void load();
       void save();
       int  search(int onLoan = 0);
       void returnPub();
       void newPublication();
       void removePublication();
       void checkOutPub();
   public:
       LibApp(const char*);
       ~LibApp();
       Publication* getPub(int libRef);
       void run();

   };
}
#endif


