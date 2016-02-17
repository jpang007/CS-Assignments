//  =============== BEGIN ASSESSMENT HEADER ================
/// @file assn<#>/main.cpp 
/// @brief Assignment/Lab <#, e.g. 1,2,3..10> for CS 12 <quarter & year>
///
/// @author <Jeremy Pang> [jpang007@ucr.edu]
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
#include "IntVector.h"
#include <iostream>
#include <cstdlib>

using namespace std;

IntVector::IntVector() {
    sz = 0;
    cap = 0;
    data = 0;
}

IntVector::IntVector(unsigned size) {
    sz = size;
    cap = size;
    data = new int[sz];
    for (unsigned i = 0; i < sz; i++) {
        data[i] = 0;
    }
}

IntVector::IntVector(unsigned size, int value) {
    sz = size;
    cap = size;
    data = new int[sz];
    for (unsigned i = 0; i < sz; i++) {
        data[i] = value;
    }
}

unsigned IntVector::size() const {
    return sz;
}

unsigned IntVector::capacity() const {
    return cap;
}

bool IntVector::empty() const{
    if (sz == 0) {
        return true;
    }
    else {
        return false;
    }
}

const int& IntVector::at(unsigned index) const {
    if (index >= sz) {
        exit(1);
    }
    else {
        return data[index];
    }
}

int& IntVector::at(unsigned index) {
    if (index >= sz) {
        exit(1);
    }
    else {
        return data[index];
    }
}

const int& IntVector::front() const {
    return data[0];    
}

int& IntVector::front() {
    return data[0];
}

const int& IntVector::back() const {
    return data[sz - 1];
}

int& IntVector::back() {
    return data[sz - 1];
}

IntVector::~IntVector() {
    delete []data;
}

void IntVector::expand() {
    cap *= 2;
    if (cap == 0) {
        cap += 1;
    }
    int* temp = new int[cap];
    for (unsigned i = 0; i < sz; i++) {
        temp[i] = data[i];
    }
    delete []data;
    data = temp;
}

void IntVector::expand(unsigned amount) {
    cap += amount;
    int* temp = new int[cap];
        for (unsigned i = 0; i < sz; i++) {
            temp[i] = data[i];
    }
    delete []data;
    data = temp;
}

void IntVector::insert(unsigned index, int value) {
    if (sz >= cap) {
        expand();
    }
    sz += 1;
    for (unsigned i = sz - 1; i < index; i--) {
        data[i] = data[i - 1];
    }
    data[index] = value;
}

void IntVector::erase(unsigned index) {
    if (index >= sz) {
        exit(1);
    }
    for (unsigned i = 0; i < (sz - 1); i++) {
        data[index + i] = data[index + 1 + i];
    }
    sz = sz - 1;
}

void IntVector::push_back(int value) {
    insert(sz, value);
}

void IntVector::pop_back() {
    if (sz == 0) {
        exit(1);
    }
    else {
        sz = sz - 1;
    }
}

void IntVector::clear() {
    sz = 0;
}

void IntVector::resize(unsigned size) {
    if (size < sz){
        sz = size; 
    }
    else if (size > sz){ 
        unsigned temp = sz;
            if (size >  2 * cap){
                expand(size - cap);
            }
            else if ( size >  cap){
                expand();
                
            }
        sz = size;
            
        for(unsigned i = temp ; i < sz; i++){
            data[i] = 0;
        }
    }
}


void IntVector::resize(unsigned size, int value) {
    if (size < sz){
        sz = size; 
    }
    else if (size > sz){ 
        unsigned temp = sz;
            if (size >  2 * cap){
                expand(size - cap);
            }
            else if ( size >  cap){
                expand();
                
            }
        sz = size;
            
        for(unsigned i = temp ; i < sz; i++){
            data[i] = value;
        }
    }
}

void IntVector::reserve(unsigned n) {
    if (n > 2 * cap) {
        expand(n - cap);
    }
    else if (n > cap) {
        expand();
    }
    else if (n < cap) {
        cap = n;
    }
}

void IntVector::assign(unsigned n, int value) {
    clear(); 
    if (n > 2 * cap) {
        expand(n - cap);
    }
    else if (n > cap) {
        expand();
    }
    resize(n,value);
}
