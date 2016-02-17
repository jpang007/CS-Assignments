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
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>

#include "BBoard.h"
#include "User.h"
#include "Message.h"
#include "Topic.h"
#include "Reply.h"

using namespace std;

BBoard::BBoard() : title("Jeremy's Bulletin Board"), current_user(NULL) {
}
BBoard::BBoard(const string &ttl) : title(ttl), current_user(NULL) {
}
BBoard::~BBoard() {
    for (unsigned i = 0; i <message_list.size();i++) {
        delete message_list.at(i);
        message_list.at(i) = 0;
    }
}
bool BBoard::load_users(const string &userfile){
    ifstream inFS;
    inFS.open(userfile.c_str());
    if(!inFS.is_open()){
        cout << "Your file cannot be opened";
        inFS.close();
        return false;
    }
    else{
        string a = "";
        string b = "";
        inFS >> a;
        do{
            inFS >> b;
            user_list.push_back(User(a,b));
            inFS >> a;
        }while(a != "end");
    }
    inFS.close();
    return true;
    
}
bool BBoard::load_messages(const string& datafile)
{
    ifstream inFS;
    bool reply = true;
    int num_msg;
    
    string begin;
    string input;
    
    unsigned inID;
    string Sub;
    string inAthr;
    string inChild;
    ostringstream c_total;
    string tostring;
    string inBdy;
    inFS.open(datafile.c_str());
    if (!inFS.is_open()) {
        cout << "Error: Cannot open file " << datafile << endl;
        return false;
    }
    
    inFS >> num_msg;
    inFS.ignore();
    int counter = 0;
    while(counter != num_msg) {
        string temp_body;
        inFS >> begin;
        if (begin == "<begin_topic>") {
            reply = false;
        }
        else if (begin == "<begin_reply>") {
            reply = true;
        }
        inFS.ignore();
        inFS >> input;
        //cout << "Input: " << input << endl;
        if (input == ":id:") {
            inFS >> inID;
        }
        inFS >> input;
        //cout << "Input: " << input << endl;
        if (input == ":subject:") {
            inFS.ignore();
            getline(inFS, Sub);
        }
        inFS >> input;
        //cout << "Input: " << input << endl;
        if (input == ":from:") {
            inFS >> inAthr;
            inFS.ignore();
        }
        
        inFS >> input;
        inFS.ignore();
        //cout << "Input: " << input << endl;
        if (input == ":children:") {
            getline(inFS, inChild);
            c_total << "# " << inID << " " << inChild << " 0 ";
            inFS >> input;
            inFS.ignore();
            //cout << "Input: " << input << endl;
        }
        
        if (input == ":body:")
        {
            getline(inFS, inBdy);
            while (inBdy != "<end>")
            {
                temp_body += inBdy;
                temp_body += '\n';
                getline(inFS, inBdy);
            }
            
            temp_body.erase(temp_body.length() - 1);
        }
        if (reply) {
            Message* ptr = new Reply(inAthr, Sub, temp_body, inID);
        
            message_list.push_back(ptr);
        }
        else {
            Message* ptr = new Topic(inAthr, Sub, temp_body, inID);
            message_list.push_back(ptr);
        }
        counter ++;
        
    }
    
    inFS.close();
    c_total << "<end>";
    tostring = c_total.str();
    istringstream inSS(tostring);
    bool finish = true;
    string hashtag;
    int index;
    int num;
    
    //fill child_list vector
    while(finish) {
        inSS >> hashtag;
        if (hashtag == "<end>") {
            finish = false;
        }
        else {
            inSS >> index;
            inSS >> num;
            while (num != 0) {
                message_list.at(index - 1)->add_child(message_list.at(num - 1));
                inSS >> num;
            }
        }
        
    }
    return true;
}
bool BBoard::save_messages(const string& datafile)
{
    ofstream outFS; 
    
    outFS.open(datafile.c_str());
    
    if (!outFS.is_open()) {
        cout << "Error opening file";
        outFS.close();
        return false;
    } 
    
    outFS << message_list.size() << endl;
    
    for (unsigned i = 0; i < message_list.size(); i++) {
        outFS << message_list.at(i) -> to_formatted_string();
    }
    
    outFS.close();
    return true;
}
void BBoard::login()
{
    string temp_uname;
    string temp_pass;
    string username;
    string pass;
    
    bool correct_user = false;
    cout << title << endl;
    while (!correct_user)
    {
        cout << "Enter your username ('Q' or 'q' to quit): ";
        cin >> username;
        
        if (username == "Q" || username == "q") {
            cout << "Bye!" << endl;
            exit(0);
        }
        else {
            cout << "Enter your password: ";
            cin >> pass;
            unsigned i = 0;
            for (i = 0; i < user_list.size(); i++)
            {
                User temp_user = user_list.at(i);
                
                if(temp_user.check(username, pass))
                {
                    correct_user = true;
                    break;
                }   
            }
            if (correct_user)
            {
                current_user = &user_list.at(i);
                cout << endl;
                cout << "Welcome back " << current_user->get_username() << '!';
                cout << endl << endl;
            }
            else
            {
                cout << "Invalid Username or Password!" << endl << endl;
            }
        }
    }
    
}
void BBoard::run() {
    string action;
    string subject, body, author;
    do 
    {
        cout << "Menu" << endl;
        cout << " - Display Messages ('D' or 'd')" << endl;
        cout << " - Add New Topic ('N' or 'n')" << endl;
        cout << " - Add Reply to reply ('R' or 'r')" << endl;
        cout << " - Quit ('Q' or 'q')" << endl;
        cout << "Choose an action: ";
        cin >> action;
        cout << endl;
        if (action == "D" || action == "d") {
            if (message_list.size() == 0) {
                cout << "Nothing to display" << endl;
            }
            else {
                for (unsigned i = 0; i < message_list.size(); i++) {

                    if(message_list.at(i)->is_reply() == false){
                        cout << "-----------------------------------------------";
                        cout << endl;                        
                        message_list.at(i)->print(0);
                    }
                }
            }
            cout << "-----------------------------------------------" << endl;
        }
        else if (action == "N" || action == "n") {
            add_topic();
        }
        else if (action == "R" || action == "r") {
        }
        else if (action == "Q" || action == "q") {
            cout << "Bye!";
            exit(0);
        }
        
    }while(action != "Q" || action != "q");
}
void BBoard::add_topic() {
    string author = current_user -> get_username();
    string subject; 
    string body, tempo = " ";
    int id = message_list.size() + 1;  
    
    cin.ignore(1000, '\n'); 
    
    cout << "Enter Subject: "; 
    getline(cin, subject);
    
    cout << "Enter Body: "; 
    
    while(tempo != "") {
        getline(cin, tempo);
        if(tempo == "") {
            break;
        }
        body = body + tempo + '\n'; 
    }
    
    body = body.substr(0, body.size() - 1); 
    
    Topic* temp = new Topic( author, subject, body, id );
    message_list.push_back(temp); 
}
