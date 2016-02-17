#include "IntList.h"
#include <iostream>
using namespace std;

int main() {
    IntList b;
    b.push_front(5);
    b.push_front(5);
    b.display();
    cout << endl;
    b.remove_duplicates();
    b.display();
    cout << endl;
    return 0;
}
