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
#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User{
    private:
        string username;
        string password;
    public:
    //creates a user with empty name and password.
        User();
    // creates a user with given username and password.
        User(const string& uname, const string& pass);
    //returns the username
        string get_username() const;
    // returns true if the stored username/password matches with the
    // parameters. Otherwise returns false.
    // Note that, even though a User with empty name and password is 
    // actually a valid User object (it is the default User), this 
    // function must still return false if given a empty uname string.
        bool check(const string &uname, const string &pass) const;
    // sets a new password. This function will not be used in the 
    // current assignment.
        void set_password(const string &newpass);
};

#endif
