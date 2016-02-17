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
#include "BBoard.h"
#include "Message.h"
#include "User.h"
#include "Topic.h"
#include "Reply.h"

#include <iostream>
#include <vector>
#include "BBoard.h"
#include "Message.h"
#include "User.h"
#include <string>
#include "Topic.h"
#include "Reply.h"

using namespace std;

int main(int argc, char **argv)
{
    // check commandline arguments 
    // (see Zyante Chapter 8, section 8.7 for explanations and examples)   
    if (argc != 3){
        cout << "ERROR: Invalid program call." << endl
            << "Usage: <program_name> userfile datafile" << endl;
        return 1;
    }
    string userfile(argv[1]);
    string datafile(argv[2]);
   
    BBoard bb("CS12 Bulletin Board");
   
    // load users from file
    if (!bb.load_users(userfile))
    {
        cout << "ERROR: Cannot load users from " << userfile << endl;
        return 1;
    }
   
    // load messages   
    if (!bb.load_messages(datafile))
    {
        cout << "ERROR: Cannot load messages from " << datafile << endl;
        return 1;
    }
   
    bb.login();
    bb.run();
    // save messages
    if (!bb.save_messages(datafile))
    {
        cout << "ERROR: Cannot save messages to " << datafile << endl;
        return 1;
    }
    bb.save_messages(datafile);
    return 0;
}
