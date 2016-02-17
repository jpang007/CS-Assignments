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
#include <iostream>
#include <string>
#include "User.h"

using namespace std;

User::User() {
    username = "";
    password = "";
}

User::User(const string &uname, const string &pass) {
    username = uname;
    password = pass;
}

string User::get_username() const {
    return username;
}


bool User::check(const string &uname, const string &pass) const {
    if (username == uname && password == pass)
	{
		return true;
	}
	else if (username == "")
	{
		return false;
	}
	else{
		return false;
	}
	return 0;
}

void User::set_password(const string &newpass) {
    password = newpass;
}
