#include "QuadraticProbing.h"
#include <iostream>
using namespace std;

/**
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */
bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}

/**
 * Internal method to return a prime number at least as large as n.
 * Assumes n > 0.
 */
int nextPrime( int n )
{
    if( n <= 0 )
        n = 3;

    if( n % 2 == 0 )
        n++;

    for( ; !isPrime( n ); n += 2 )
        ;

    return n;
}

/**
 * A hash routine for string objects.
 */
int hash( const string & key )
{
    int hashVal = 0;

    for( int i = 0; i < key.length( ); i++ )
        hashVal = 37 * hashVal + key[ i ];

    return hashVal;
}

int superhash(const string & key) {
    int hashVal = 0;
    unsigned ch;
        int highorder = hashVal & 0xf8000000; // extract high-order 5 bits from hashVal
        // 0xf8000000 is the hexadecimal representation
        // for the 32-bit number with the first five
        // bits = 1 and the other bits = 0
        hashVal = hashVal << 5; // shift hashVal left by 5 bits
        hashVal = hashVal ^ (highorder >> 27); // move the highorder 5 bits to the
        // low-order end and XOR into hashVal
        hashVal = hashVal ^ ch; // XOR ch into hashVal
    
    return hashVal;
}

/**
 * A hash routine for ints.
 */
int hash( int key )
{
    return key;
}
