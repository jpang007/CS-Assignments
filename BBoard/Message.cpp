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
#include "Message.h"
#include <string>
#include <iomanip>
using namespace std;
Message::Message(){
    author = "";
    subject = "";
    body = "";
    id = 0;
}
Message::Message(const string &athr, const string &sbjct, const string &body, unsigned id){
    author = athr;
    subject = sbjct;
    this->body = body;
    this->id = id;
}
Message::~Message(){
    for (unsigned i = 0; i < child_list.size(); i++){
        child_list.at(i) = 0;
    }
}
void Message::print(unsigned indentation) const{
    string indent;
    if (indentation != 0) {
        for (unsigned i = 0; i < indentation; i++) {
            indent += "  ";
        }
    }
    
    cout << indent;
     
    cout << "Message #" << id << ": " << subject << endl;
     
    cout << indent;
     
    cout << "from " << author << ": ";
     
    for (unsigned i = 0; i < body.length(); i++)
    {
        if (body.at(i) == '\n')
        {
            cout << body.at(i);
            cout << indent;
        }
        else
        {
            cout << body.at(i);
        }
    }
    
    cout << endl;
    if (!child_list.empty())
    {
        for (unsigned i = 0; i < child_list.size(); i++)
        {
            child_list.at(i)->print(indentation + 1);
        }
    }
}
const string & Message::get_subject() const{
    return subject;
}
unsigned Message::get_id() const{
    return id;
}
void Message::add_child(Message *child){
    child_list.push_back(child);
}
