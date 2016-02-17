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
#ifndef INTVECTOR_H
#define INTVECTOR_H

using namespace std;

class IntVector {
    private:
    unsigned sz;
    unsigned cap;
    int* data;
    public:
    IntVector();
    IntVector(unsigned sz);
    IntVector(unsigned sz, int value);
    ~IntVector();
    unsigned size() const;
    unsigned capacity() const;
    bool empty() const;
    const int &at(unsigned index) const;
    int & at(unsigned index);
    void insert(unsigned index, int value);
    void erase(unsigned index);
    const int& front() const;
    int& front();
    const int& back() const;
    int& back();
    void assign(unsigned n, int value);
    void push_back(int value);
    void pop_back();
    void clear();
    void resize(unsigned size);
    void resize(unsigned size, int value);
    void reserve(unsigned n);
    private:
    void expand();
    void expand(unsigned amount);
};

#endif
