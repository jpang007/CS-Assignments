#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <ctype.h>
#include "QuadraticProbing.h"
#include "SeparateChaining.h"

using namespace std;

// Actual driver ready to do work
int collisioncounter;

string toLowerCase(string s) // function to help convert words to all lower case
{
    string r = s;
    for (int i = 0; i < r.size(); i++)
        if (r[i] >= 'A' && r[i] <= 'Z')
            r[i] = tolower(r[i]);
    return r;
}

void removePunct(string & str)
{
	str.erase(remove_if(str.begin(), str.end(), static_cast<int(*)(int)>(&ispunct)),str.end());
}

int main(int argc, char *argv[]) {
    vector <string> inputfiles; // vector of string to hold whats inside the command line
    vector <string> Dictionarywords; // vector of the dictionary words to compare to
    vector <string> takeinfiles; // vector to hold string *toupper & *tolower the
    string inputtedfilename, inputtedfilename2, inputtedfilename3, firstoutput, secondoutput;
    // 1) first command line argument 2) second one 3) third one 4) string to output to .out 5) string to 
    // output to .stats
    string outputfilename; // string used to attached suffix to output files .stats and .out
    string inputline; // string for inputting text into vector 
    string line1, line2; // the strings used to help dechiper the command line
    vector <int> chaincounter; // holds all the length of list for chaining 
    
    ifstream the_input(argv[3]); // Opens the file and pushes back everything into a string
    if (!the_input.is_open() ) {
        cout<<"Could not open file\n";
    }
    else {
    string x;
    while (the_input >> x ) {
        removePunct(x);
        inputfiles.push_back(x);
    }

    }
    
    cout << "All words in inputted file lowercase are: " << endl;
    for (int i = 0; i < inputfiles.size(); i++) { // converts all the elements in vector<string> inputfiles
    // to lowercase and prints them out to check
        inputfiles[i] = toLowerCase(inputfiles[i]);
        cout << inputfiles[i] << " ";
    }
    cout << endl;
    
    /*
    for (int i = 0; i < inputfiles.size(); i++) { // just to check whats inside
        cout << inputfiles.at(i) << " ";
    }
    */
    
    inputtedfilename = argv[1]; // looks at the first command line to see which command to do
    inputtedfilename2 = argv[2]; // looks at the second command line to see which command to do
    inputtedfilename3 = argv[3]; // Attaches the correct name and suffix to output files
    
    ifstream inputgobblegobble; // ifstream caled inputgobblegobble
    inputgobblegobble.open(inputtedfilename3.c_str()); // inputgobblegobble opens inputted
    //filename 3 aka input.txt
    ofstream output, output2; // creates two ofstream output, output for .stats and .out
    ifstream dictionaryinput; // holds the .txt files of the two dictionary libraries later
    
    int periodfound = inputtedfilename3.find('.');
    inputtedfilename3 = inputtedfilename3.substr(0,periodfound); // Translates inputtedfilename3 
    // substrings at the . so it can accept name suffix input file
    
    firstoutput = inputtedfilename3 + ".out";
    secondoutput = inputtedfilename3 + ".stats";
    
    if (inputgobblegobble.is_open()) {
        if (inputtedfilename == "-1") {
            cout << "Selected Smalldic.txt " << endl;
            dictionaryinput.open("Smalldic.txt");
            while (getline(dictionaryinput, inputline)) {
                Dictionarywords.push_back(inputline); // Uses the Smalldic.txt and
                // push_backs all the words into a vector<string> 
            }
            cout << "Total words stored in string Dictionarywords: " << Dictionarywords.size() << endl;
        }
        
        if (inputtedfilename == "-2") {
            cout << "Selected Ispell.txt " << endl;
            dictionaryinput.open("Ispell.txt");
            while(getline(dictionaryinput, inputline)) {
                Dictionarywords.push_back(inputline); //Uses the Ispell.txt and 
                //push_backs all the words into a vector<string>
            }
            cout << "Total words stored in string Dictionarywords: " << Dictionarywords.size() << endl;
        }
        
        if (inputtedfilename2 == "-chain") { // If the user specififes using a chain
            HashTableS<int> h1;
            
            cout << ">>Selected Chain ";
            int i, spot = 0;
            
            for (i = 0; i != Dictionarywords.size(); i++) {
                h1.insertS(hashS(Dictionarywords[i])); // makes a hashtable of the dictionary words
            }
            
            for (i = 0; i != Dictionarywords.size(); i++) { // If no ERROR then all files are present
                if (h1.containsS(hashS(Dictionarywords[i]) ) == false) {
                    cout << "ERROR" << endl;
                }
            }
            
            output.open(firstoutput.c_str());
                for (i = 0; i != inputfiles.size(); i++) {
                    if (h1.containsS(hashS(inputfiles[i])) == false) { // if the dictionary hash table
                    // does not contain the mispelled words throw those into a output.txt
                        output << inputfiles[i] << endl;
                    }
                }
            output.close();
            
            cout << endl;
            output2.open(secondoutput.c_str());
            output2 << "Length of tables | " << "Table entries that appeared" << endl;
            for (int i = 0; i < inputfiles.size(); i++ ) {
                int holdera = h1.mahchain(hashS(inputfiles[i]));
                cout << holdera;
                chaincounter.push_back(holdera);
            }
            
            sort(chaincounter.begin(), chaincounter.end());
        
            for (int i = 0; i < chaincounter.size(); i++) { // double for loop to output the chaincounter
                int countercounter = 0;
                if (chaincounter[i] != chaincounter[i + 1]) {
                    output2 << chaincounter[i] << "                    ";
                    if (i == 0) {
                        countercounter++;
                    }
                    for (int z = 0; z < chaincounter.size() - 1; z++) {
                        if (chaincounter[i] == chaincounter[z + 1]) {
                            countercounter++;
                        }
                    }
                    output2 << countercounter;
                    output2 << endl;
                    }
            }
            output2.close();
            
        }
        
        else if (inputtedfilename2 == "-probe") { // If the user specifies using a probe
            HashTable<int> a1;
            
            cout << ">>Selected Probe" << endl;
            
                int i, spot = 0;
                vector<int> collisioncounterholder;
                for( i = 0; i != Dictionarywords.size(); i++) {
                    a1.insert(hash(Dictionarywords[i]));
          
                    collisioncounterholder.push_back(collisioncounter);
                }
                
                for (i = 0; i != Dictionarywords.size(); i++) { // If no ERROR then all files are present
                    if (a1.contains(hash(Dictionarywords[i]) ) == false) {
                        cout << "ERROR" << endl;
                    }
                }
                
                output.open(firstoutput.c_str());
                for (i = 0; i != inputfiles.size(); i++) {
                    if (a1.contains(hash(inputfiles[i])) == false) {
                        output << inputfiles[i] << endl;
                    }
                }
                output.close();
                
                output2.open(secondoutput.c_str());
                output2 << "Number of collisions | " << "Number of dictionary words experiencing collsion" << endl;

                
                sort(collisioncounterholder.begin(), collisioncounterholder.end());
                
                for (int i = 0; i < collisioncounterholder.size(); i++) { // double for loop to output the
                // collisioncounter
                int countercounter = 0;
                if (collisioncounterholder[i] != collisioncounterholder[i + 1]) {
                    output2 << collisioncounterholder[i] << "                    ";
                    if (i == 0) {
                        countercounter++;
                    }
                    for (int z = 0; z < collisioncounterholder.size() - 1; z++) {
                        if (collisioncounterholder[i] == collisioncounterholder[z + 1]) {
                            countercounter++;
                        }
                    }
                    output2 << countercounter;
                    output2 << endl;
                    }
            }
            output2.close();
        }

    }
    
    cout << endl;
    return 0;
}
