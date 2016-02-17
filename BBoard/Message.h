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
#ifndef MESSAGE_H
#define MESSAGE_H
#include <iostream>
#include <vector>
#include <string>

using namespace std;

 class Message { 
    protected:
        string author;
        string subject;
        string body;
        unsigned id; // New !!
        vector<Message*> child_list; // New !!
    public:
        Message();
        Message(const string& athr, const string& sbjct, const string& body, 
 unsigned id);
        virtual ~Message();
        virtual bool is_reply() const = 0;
        virtual string to_formatted_string() const = 0; // New!!
        void print(unsigned indentation) const; // New !!
 //returns the subject string.
        const string& get_subject() const;
 // returns the id.
        unsigned get_id() const; // New !! 
 // Adds a pointer to the child to the parent's child_list. 
        void add_child(Message* child); // New !! 

 };

#endif
