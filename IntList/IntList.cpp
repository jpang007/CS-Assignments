#include "IntList.h"
#include <iostream>
#include <algorithm>
using namespace std;

IntList::IntList() {
    head = 0;
    tail = 0;
}

IntList::~IntList() {
    while(head != 0) {
        pop_front();
    }
}

void IntList::display() const {
    IntNode *curr = head;
    while (curr != 0){
        cout << curr->data;
        curr = curr -> next;
        if (curr != 0){
            cout << ' ';
        }
    }
}

void IntList::push_front(int value) {
    IntNode *tmp = new IntNode(value);
    tmp -> next = head;
    head = tmp ;
    if ( tail == 0){
        tail = head; 
    }
}

void IntList::push_back(int value) {
    IntNode *tmp = new IntNode(value);
    if (tail == 0) {
        tail = tmp;
        if (head == 0) {
            head = tmp;
        }
        return;
    }
    tail -> next = tmp;
    tail = tmp;

}

void IntList::pop_front() {
    if(head == 0){
        return;
    }
    IntNode* temp = head; 
    head = head -> next;
    delete temp;
}

void IntList::select_sort() {
    IntNode *i;
    IntNode *j;
    IntNode *min;
    int value;
    for (i = head; i != 0; i = i->next) {
        
        min = i;
        
        for (j = i->next; j != 0; j = j->next) {
            
            if (j->data < min->data) {
                
                min = j;
            }
        }
        value = i->data;
        i->data = min->data;
        min->data = value;
    }
}

void IntList::insert_sorted(int value) {
    IntNode *prev;
    IntNode *curr;

    if (head == 0)  {
        push_front(value);
 
    }
    else if (value >= tail->data) {
        push_back(value);
  
    }
    else if (value <= head->data) {
        push_front(value);
 
    }
    else {
        IntNode *tmp = new IntNode(value);
        for(prev = head; prev->next != curr; prev = prev->next) {
            curr = prev->next;
            if (value >= prev->data && value <= curr->data) {
                prev->next = tmp;
                tmp->next = curr;
                return;
            }
        }
            delete tmp;
    }
    
}

void IntList::remove_duplicates() {
    
    IntNode *a;
    IntNode *b;
    if (head == tail) {
        return;
    }
    for(a = head; a != 0; a = a -> next) {
        IntNode *c;
        for(b = a, c = b -> next; c != 0; c = b -> next) {
            if(c -> data == a -> data) {
                b -> next = c -> next;
                if(c == tail) {
                    tail = b;
                }
                delete c;
            }
            else {
                b = b -> next;
                
            }
        }
        
    }
    
}
