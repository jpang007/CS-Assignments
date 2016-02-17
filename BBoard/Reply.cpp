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
#include "Reply.h"

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

Reply::Reply() : Message() {
    
}

Reply::Reply(const string& athr, const string& sbjct, const string& body, 
 unsigned id) : Message(athr,sbjct,body,id) {
     
 }
 
bool Reply::is_reply() const{
    return true;
}

string Reply::to_formatted_string() const {
    string reply;
    stringstream outFS;
    
    outFS << "<begin_reply>\n:id: " 
    << id << "\n:subject: " << subject <<
    "\n:from: " << author;
    
    if(child_list.size() != 0) {
        outFS << "\n:children: ";
        
        for (unsigned i = 0; i < child_list.size(); i++) {
            outFS << (child_list.at(i) -> get_id());
            
        }
    }
    
    outFS << "\n:body: " << body << '\n' << "<end>" << '\n';
    reply = outFS.str();
    return reply;
}
