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
#include "Topic.h"
#include "Message.h"
#include <sstream>
#include <vector>
#include <string>

using namespace std;

Topic::Topic() 
    :Message() {
}

Topic::Topic(const string &athr, const string &sbjct, const string &body,
unsigned id) : Message(athr,sbjct,body,id) {
}

bool Topic::is_reply() const {
    return false; 
}

string Topic::to_formatted_string() const {
    string topic;
    stringstream outFS;
    
    outFS << "<begin_topic>\n:id: " 
    << id << "\n:subject: " << subject <<
    "\n:from: " << author;
    
    if(child_list.size() != 0) {
        outFS << "\n:children: ";
        
        for (unsigned i = 0; i < child_list.size(); i++) {
            outFS << (child_list.at(i) -> get_id());
            
        }
    }
    
    outFS << "\n:body: " << body << '\n' << "<end>" << '\n';
    topic = outFS.str();
    return topic;
}

