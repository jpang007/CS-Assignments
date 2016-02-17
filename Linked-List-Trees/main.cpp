#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <sstream>
#include "assn4.h"
#include <list>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;


int main(int argc, char *argv[]) {

    vector <string> inputfiles;
    string inputtedfilename, firstoutput, relationshipseperator;
    string line1, line2;
    ofstream output;
    list<Fraction> ab, originalforumula;
        
    ifstream the_input(argv[1]); // Opens the file and pushes back everything into a string
    if (!the_input.is_open() ) {
        cout<<"Could not open file\n";
    }
    else {
    string x;
    while (the_input >> x )
        inputfiles.push_back(x);
    }
        
    //for (int i = 0; i < inputfiles.size(); i++) { // just to check whats inside
    //    cout << inputfiles.at(i) << " ";
    //}
    
    string yolo;  // Beings to seperate the input.txt into parts line by line 
    yolo = argv[1];
    
    ifstream inputgobblegobble;
    inputgobblegobble.open(yolo.c_str());
    
    if (inputgobblegobble.is_open()) {
        inputtedfilename = argv[1]; // Attaches the correct name and suffix to output files
                
        inputtedfilename = inputtedfilename.substr(0, inputtedfilename.size() - 4);
                
        firstoutput = inputtedfilename + ".out";
            
        output.open(firstoutput.c_str());
        while (inputgobblegobble.good()) {
            vector <int> a;
            vector <int> outputvector;
            getline(inputgobblegobble, line1);
            getline(inputgobblegobble, line2);
            
            cout << line1 << endl;
            cout << line2 << endl;
            
            if (line1 == "f") { // if fraction
                if stream(line2);
                int temp = 0;
                while(stream >> temp) {
                    a.push_back(temp);
                }
                
                for (int i = 0; i < a.size() - 1; i = i + 2) {
                        ab.push_back(Fraction(a[i], a[i + 1])); // list to be altered
                        originalforumula.push_back(Fraction(a[i], a[i + 1])); // original list to be entered into tree
                } 
                
                cout << endl; 
                
                
                list<Fraction>::iterator spot1;
                spot1 = ab.begin();
                spot1++;
                while (spot1 != ab.end()) {
                    if (*spot1 == ab.front()) {
                        spot1 = ab.erase(spot1);
                    }
                    else {
                        spot1++;
                    }
                } // loop goes thro AB and deletes anything that matches the first value
                
                cout << "New list is: ";
                
                for (list<Fraction>::iterator it=ab.begin(); it != ab.end(); ++it) {
                cout << ' ' << *it;
                }
                
                cout << endl;
                
                list<Fraction>::iterator itr;

                output << line1 << endl;
	            for(itr= ab.begin(); itr != ab.end();++itr)
	            {
	                output<< *itr << " ";
	            }
	            output << endl; // for loop prints out the new edited list

                cout << endl;
                

                obtree fractiontree;
                list<Fraction>::iterator obtreeitr;
                obtreeitr = originalforumula.begin();
                while(obtreeitr != originalforumula.end()) {//error here 
                    fractiontree.insertf(obtreeitr); // doesnt work because it only takes in int
                    obtreeitr++;
                }
                cout << "Values in tree are in order: ";
                fractiontree.print_inorderf();
                cout << endl;
                cout << "Values in tree are postorder: ";
                fractiontree.print_postorderf();
                
                originalforumula.clear();
                
                fractiontree.sortf(originalforumula);
                cout << endl;
                cout << "Ordered list: ";
                for (list<Fraction>::iterator it=originalforumula.begin(); it != originalforumula.end(); ++it) {
                cout << ' ' << *it;
                }
                        // TODO:: Figure out a way to either input a int or take in a Fraction
                originalforumula.clear();
                ab.clear();
                    
                cout << endl << endl;
            }
            
            else if (line1 == "i") { // if list is int
                vector <int> a, originala;
                stringstream stream(line2);
                int temp = 0;
                while(stream >> temp) {
                    a.push_back(temp);
                    originala.push_back(temp);
                }
                
                int x = a[0];
                for (int i = 1; i < a.size(); i++) { // input values into a vector<int> then erase the similar ones
                    if (x == a[i]) {
                        a.erase(a.begin() + i);
                    }
                }
                
                for (int i = 0; i < originala.size(); i = i + 1) {
                        ab.push_back(Fraction(originala[i])); // list to be altered
                        originalforumula.push_back(Fraction(originala[i])); // original list to be entered into tree
                } 
                cout << "New list is: ";
                
                for (list<Fraction>::iterator it=ab.begin(); it != ab.end(); ++it) {
                cout << ' ' << *it;
                }
                
                list<Fraction>::iterator itr;
            
                output << line1 << endl;
	            for(itr= ab.begin(); itr != ab.end();++itr)
	            {
	                output<< *itr << " ";
	            }
	            output << endl; 
                obtree inttree; // make a binary tree of ints
                
                cout << endl;
                int n = 1, i = 0;
                while (n == 1) {
                    inttree.insert(originala[i]);
                    i++;
                    if (i == originala.size()) {
                        n = 0;
                    }
                }
                
                cout << endl;
                cout << "Values in the tree are postorder: ";
                
                inttree.print_postorder();
                
                cout << endl;
                cout << "Values in the tree are in order: ";
                inttree.print_inorder();
                cout << endl;
                
 
                
                inttree.sortf(originalforumula);
                
                for (list<Fraction>::iterator it=originalforumula.begin(); it != originalforumula.end(); ++it) {
                cout << ' ' << *it;
                }
                
                ab.clear();
                originalforumula.clear();

                cout << endl;
            }
            
            
        }
            
        cout << endl;
    }
    
    
    
    return 0;     
}
    
        
