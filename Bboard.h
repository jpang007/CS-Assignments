//  =============== BEGIN ASSESSMENT HEADER ================
/// @file assn<#>/main.cpp 
/// @brief Assignment/Lab <#, e.g. 1,2,3..10> for CS 12 <quarter & year>
///
/// @author <Your name> [fake@email.com]
/// @date <Current date>
///
/// @par Enrollment Notes 
///     Lecture Section: <e.g. 001>
/// @par
///     Lab Section: <e.g. 021>
/// @par
///     TA: <TA name>
///
/// @par Plagiarism Section
/// I hereby certify that the code in this file
/// is ENTIRELY my own original work.
//  ================== END ASSESSMENT HEADER ===============
#ifndef BBoard_H
#define BBoard_H

#include <iostream>
#include <string>
#include <vector>
#include "User.h"
#include "Message.h"
using namespace std;

class BBoard {
    private:
    string title;
    vector<User> user_list;
    const User* current_user;
 	vector<Message *> message_list;
 	
    public:
    BBoard();
    BBoard( const string &ttl );
    ~BBoard();
    bool load_users(const string &userfile);
    void login( );
    void run( );
    bool load_messages(const string& datafile);
    bool save_messages(const string& datafile);
    
    private:
    void add_topic();
    void add_reply();
    
};

#endif
