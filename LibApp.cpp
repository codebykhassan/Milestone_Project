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
/***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;
#include "LibApp.h"
#include "Menu.h"
#include "Publication.h"
#include "Book.h"
#include "PublicationSelector.h"

namespace seneca {

LibApp::LibApp(const char* fileName) : m_changed(false), m_mainMenu("Seneca Library Application"), m_exitMenu("Changes have been made to the data, what would you like to do?"), m_typeMenu("Choose the type of publication:") {
    NOLP = 0;
    LLRN = 0;
    m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
    m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
    m_typeMenu << "Book" << "Publication";
    strcpy(m_fileName, fileName);
    load();
}
LibApp::~LibApp(){
    for (int i = 0; i < NOLP; ++i) {
        delete PPA[i];
    }
}
bool LibApp::confirm(const char *message){
    Menu menu(message);
    menu << "Yes";
    return menu.run() == 1;
}
void LibApp::load(){
    cout << "Loading Data" << endl;
    ifstream file(m_fileName);
    if (!file) {
        cout << "Failed to open file: " << m_fileName << endl;
        return;
    }
    char type;
    while (file) {
        file >> type;
        file.ignore();
        if(file){
            if (type == 'B') {
                PPA[NOLP] = new Book();
            } else if (type == 'P'){
                PPA[NOLP] = new Publication();
            }
            if (PPA[NOLP] && NOLP < SENECA_LIBRARY_CAPACITY) {
                file >> *PPA[NOLP];
                LLRN = PPA[NOLP]->getRef();
                ++NOLP;
            }
        }
    }
    file.close();
}
void LibApp::save(){
    cout << "Saving Data" << endl;
    ofstream file(m_fileName);
    if (!file) {
        cout << "Failed to open file for writing." << endl;
        return;
    }
    for (int i = 0; i < NOLP; ++i) {
        if (PPA[i]->getRef() != 0) {
            file << *PPA[i] << endl;
        }
    }
    file.close();
}
int LibApp::search(int onLoan){
    PublicationSelector selector("Select one of the following found matches:");
    char s;
    char title[256];
    switch (m_typeMenu.run()) {
        case 1:
            s = 'B';
            break;
        case 2:
            s = 'P';
            break;
        default:
            cout << "Aborted!" << endl;
            return 0;
    }
    cin.ignore(1000, '\n');
    cout << "Publication Title: ";
    cin.getline(title, 256);
    bool isFound = false;
    for (int i = 0; i < NOLP; i++)
    {
        if (PPA[i]->type() == s && strstr(*PPA[i], title) &&
            (onLoan == 0 || (onLoan == 1 && PPA[i]->onLoan()) || (onLoan == 2 && !PPA[i]->onLoan())))
        {
            selector << PPA[i];
            isFound = true;
        }
    }
    if (isFound) {
        selector.sort();
        int ref = selector.run();
        if (ref) {
            cout << *getPub(ref)<< endl;
            return ref;
        }
        else {
            cout << "Aborted!" << endl;
        }
    }
    else {
        cout << "No matches found!" << endl;
    }
    return 0;
    
}
void LibApp::returnPub(){
    cout << "Return publication to the library" << endl;
    int libRef = search(1);
    if (libRef == 0) {
        return;
    }
    Publication* pub = getPub(libRef);
    if (pub && confirm("Return Publication?")) {
        Date date;
        int daysLate = date - pub->checkoutDate();
        if (daysLate > SENECA_MAX_LOAN_DAYS) {
            double penalty = (daysLate - SENECA_MAX_LOAN_DAYS) * 0.50;
            cout << "Please pay $" << fixed << setprecision(2)<< penalty << " penalty for being " << daysLate - SENECA_MAX_LOAN_DAYS << " days late!" << endl;
        }
        pub->set(0);
        m_changed = true;
        cout << "Publication returned" << endl;
    }
}
void LibApp::newPublication(){
    if (NOLP == SENECA_LIBRARY_CAPACITY) {
        cout << "Library is at its maximum capacity!" << endl;
        return;
    }
    cout << "Adding new publication to the library" << endl;
    int type = m_typeMenu.run();
    cin.ignore();
    if (type == 0) {
        cout << "Aborted!" << endl;
        return;
    }
    Publication* pub = nullptr;
    if (type == 1) {
        pub = new Book();
    }else if (type == 2){
        pub = new Publication();
    }
    if (pub) {
        cin >> *pub;
        if (cin.fail()) {
            cin.clear();
            cin.ignore('\n');
            delete pub;
            cout << "Aborted!" << endl;
            return;
        }
        if (confirm("Add this publication to the library?")) {
            LLRN++;
            pub->setRef(LLRN);
            PPA[NOLP++] = pub;
            m_changed = true;
            cout << "Publication added" << endl;
        } else{
            cout << "Failed to add publication!"<< endl;
            delete pub;
        }
        
    }
}
void LibApp::removePublication(){
    cout << "Removing publication from the library" << endl;
    int libRef = search();
    if (libRef != 0) {
        Publication* pub = getPub(libRef);
        if (pub) {
            if (confirm("Remove this publication from the library?")) {
                pub->setRef(0);
                m_changed = true;
                cout << "Publication removed" << endl;
            }else{
                cout << "Aborted!" << endl;
            }
        }
    }
}
void LibApp::checkOutPub(){
    cout << "Checkout publication from the library" << endl;
    int libRef = search(2);
    if (libRef != 0) {
        Publication* pub = getPub(libRef);
        if (pub) {
            if (confirm("Check out publication?")){
                int memID;
                cout << "Enter Membership number: ";
                while (!(cin >> memID) || memID < 10000 || memID > 99999) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid membership number, try again: ";
                }
                pub->set(memID);
                m_changed = true;
                cout << "Publication checked out" << endl;
            }else{
                cout << "Aborted!" <<endl;
            }
        }
    }
}
void LibApp::run(){
    bool done = false;
    while (!done) {
        switch (m_mainMenu.run()) {
            case 1:
                newPublication();
                break;
            case 2:
                removePublication();
                break;
            case 3:
                checkOutPub();
                break;
            case 4:
                returnPub();
                break;
            case 0:
                if (m_changed) {
                    unsigned int exitSelection = m_exitMenu.run();
                    if (exitSelection == 1) {
                        save();
                        done = true;
                    } else if (exitSelection == 0) {
                        if (confirm("This will discard all the changes are you sure?")) {
                            done = true;
                        }
                    }
                } else {
                    done = true;
                }
                break;
            default:break;
        }
        cout << endl;
    }
    cout << "-------------------------------------------" << endl;
    cout << "Thanks for using Seneca Library Application" << endl;
}
Publication* LibApp::getPub(int libRef) {
    for (int i = 0; i < NOLP; ++i) {
        if (PPA[i] && PPA[i]->getRef() == libRef) {
            return PPA[i];
        }
    }
    return nullptr;
}

}

