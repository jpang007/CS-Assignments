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
#ifndef TOPIC_H
#define TOPIC_H
#include "Message.h"
#include <string>

using namespace std;

 class Topic : public Message { 
    public:
        Topic();
        Topic(const string &athr, const string &sbjct, const string &body, unsigned id);
        virtual bool is_reply() const; // Returns false
        virtual string to_formatted_string() const; // New !!
};

#endif
