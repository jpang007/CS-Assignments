#include <iostream>
#include <vector>

using namespace std;

int setcounter = 1;

vector<int> repeatmod(int number1, int number2, int m) {
    setcounter++;
    vector<int> fibmodulus;
    vector<int> finalvector;
    fibmodulus.reserve(m * m);
    int firstvalue, secondvalue;
    int valueCheck = 0;
    int frequencyNumber = 0;
    string remainingpairs;
    fibmodulus.push_back(number1);
    fibmodulus.push_back(number2);
    
    for (int i = 2; i < m*m; i++) {
        fibmodulus.push_back((fibmodulus[i - 1] + fibmodulus[i - 2]) % m);
    }
    
    for (int i = 1; i < fibmodulus.size(); i++) {
        int x = 0;
        firstvalue = fibmodulus[x];
        secondvalue = fibmodulus[x + 1];
        if (fibmodulus[i] == firstvalue && fibmodulus[i + 1] == secondvalue) {
            fibmodulus.resize(i);
        }
    }
    
    //Finding the first set
    cout << "Set " << setcounter << " { ";
    for (int i = 0; i < fibmodulus.size(); i++) {
        cout << fibmodulus[i] << " ";
    }
    cout << "}" << endl;
    
    //Finding the frequency of values
    cout << "Frequency: { ";
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < fibmodulus.size(); j++)
        {
            if (valueCheck == fibmodulus[j])
            {
                frequencyNumber++;
            }
        }
        cout << valueCheck << ":" << frequencyNumber << " ";
        frequencyNumber = 0;
        valueCheck++;
    }
    cout << "}" << endl;
    
    // Finding all the ordered pairs within the first set
    cout << "Ordered Pairs: { ";
    for (int i = 0; i < fibmodulus.size(); i++) {
        cout << "(" << fibmodulus[i] << ", " << fibmodulus[i + 1] << ") ";
    }
    cout << "}" << endl;
    
    cout << endl;
    
    return fibmodulus;
}

vector<int> fibmod(int number1, int number2, int m)
{
    vector<int> fibmodulus;
    fibmodulus.reserve(m * m);
    int firstvalue, secondvalue;
    int valueCheck = 0;
    int frequencyNumber = 0;
    string remainingpairs;
    fibmodulus.push_back(number1);
    fibmodulus.push_back(number2);
    
    for (int i = 2; i < m*m; i++) {
        fibmodulus.push_back((fibmodulus[i - 1] + fibmodulus[i - 2]) % m);
    }
    
    for (int i = 1; i < fibmodulus.size(); i++) {
        int x = 0;
        firstvalue = fibmodulus[x];
        secondvalue = fibmodulus[x + 1];
        if (fibmodulus[i] == firstvalue && fibmodulus[i + 1] == secondvalue) {
            fibmodulus.resize(i);
        }
    }
    
    
    
    
    //Finding the first set
    cout << "Set " << setcounter << " { ";
    for (int i = 0; i < fibmodulus.size(); i++) {
        cout << fibmodulus[i] << " ";
    }
    cout << "}" << endl;
    
    //Finding the frequency of values
    cout << "Frequency: { ";
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < fibmodulus.size(); j++)
        {
            if (valueCheck == fibmodulus[j])
            {
                frequencyNumber++;
            }
        }
        cout << valueCheck << ":" << frequencyNumber << " ";
        frequencyNumber = 0;
        valueCheck++;
    }
    cout << "}" << endl;
    
    // Finding all the ordered pairs within the first set
    cout << "Ordered Pairs: { ";
    for (int i = 0; i < fibmodulus.size(); i++) {
        cout << "(" << fibmodulus[i] << ", " << fibmodulus[i + 1] << ") ";
    }
    cout << "}" << endl;
    
    cout << endl;
    
    cout << "Would you like to see the remaining ordered pairs? (Y/N) ";
    cin >> remainingpairs;
    if (remainingpairs == "Y") {
        // Fills the array with values >= 0
        int arr[m][m];
        for (int i = 0; i < m; i++) {
            int arrayfiller = 0;
            for (int y = 0; y < m; y++) {
                arr[i][y] = arrayfiller;
                arrayfiller++;
            }
        }
        // checks the array and if zero value + first value of fibmod are equal 
        // to the position in the 2D array set the value to -1 
        // Since we're checking only for values >= 0
        for (int i = 0; i < m; i++) {
            for (int y = 0; y < m; y++) {
                for (int x = 0; x < fibmodulus.size(); x++) {
                    if (fibmodulus[x] == i && fibmodulus[x + 1] == y) {
                        arr[i][y] = -1;
                    }
                }
            }
        }
        // the repeat section
        // uses repeatmod to get a new fibsequence with two new values
        // vector result is using the spots that ARE >= 0 hence the spots that weren't filled by the first loop above
        // Then the inside triple for loop is running all the spots of arr against the result values
        // So that it checks each spot and if result values are equal to it 
        // It sets it to -1
        for (int i = 0; i < m; i++) {
            for (int y = 0; y < m; y++) {
                    if (arr[i][y] >= 0) {
                    vector<int> result = repeatmod(i,y,m);
                    for (int z = 0; z < result.size(); z++) {
                        for (int a = 0; a < m; a++) {
                            for (int b = 0; b < m; b++) {
                                if (result[z] == a && result[z + 1] == b) {
                                arr[a][b] = -1;
                                }
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i < m; i++) {
            for (int y = 0; y < m; y++) {
                cout << arr[i][y] << " ";
            }
            cout << endl;
        }
        
    }
    if (remainingpairs == "N") {
        cout << "Done";
    }
    
    
    return fibmodulus;
}

vector<int> fibmod(int m)
{
    vector<int> empty;
    int num1, num2;
    cout << "Enter first value: ";
    cin >> num1;
    cout << endl;
    cout << "Enter second value: ";
    cin >> num2;
    cout << endl;
    
    if (num1 > m || num2 > m) {
        cout << "program can not run";
    }
    else {
       return fibmod(num1, num2, m);
    }
    
    return empty;
}



int main()
{
    string remainingpairs;
    int numbermod;
    
    cout << "What would you like to mod your sequence by? ";
    cin >> numbermod;
    if (numbermod < 2) {
        cout << "program can not work";
    }
    else {
       fibmod(numbermod); 
    }
    
    cout << endl;
    
    
    
    
    return 0;
}
