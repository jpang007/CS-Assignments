#ifndef SEPARATE_CHAINING_H
#define SEPARATE_CHAINING_H

#include <vector>
#include <list>
#include <string>
#include <algorithm>
using namespace std;


int nextPrimeS( int n );

// SeparateChaining Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hash( string str ) --> Global method to hash strings
int hashS( const string & key );
int hashS( int key );
int superhashS(const string & key);

template <typename HashedObjS>
class HashTableS
{
  public:
    explicit HashTableS( int size = 101 )
      : currentSize( 0 )
      { theLists.resize( 101 ); }

    bool containsS( const HashedObjS & x ) const
    {
        const list<HashedObjS> & whichList = theLists[ myhashS( x ) ];
        return find( whichList.begin( ), whichList.end( ), x ) != whichList.end( );
    }

    void makeEmptyS( )
    {
        for( int i = 0; i < theLists.size( ); i++ )
            theLists[ i ].clear( );
    }

    bool insertS( const HashedObjS & x )
    {
        list<HashedObjS> & whichList = theLists[ myhashS( x ) ];
        if( find( whichList.begin( ), whichList.end( ), x ) != whichList.end( ) )
            return false;
        whichList.push_back( x );

            // Rehash; see Section 5.5
        if( ++currentSize > theLists.size( ) )
            rehashS( );

        return true;
    }

    bool remove( const HashedObjS & x )
    {
        list<HashedObjS> & whichList = theLists[ myhashS( x ) ];
        typename list<HashedObjS>::iterator itr = find( whichList.begin( ), whichList.end( ), x );

        if(itr == whichList.end( ) )
            return false;

        whichList.erase( itr );
        --currentSize;
        return true;
    }
    
    int mahchain(const HashedObjS & x) {  // gets the size of whichlist
        int length = 0;
        list<HashedObjS> & whichList = theLists[ myhashS( x ) ];
        
        length = whichList.size();
        
        return length;
    }

  private:
    vector<list<HashedObjS> > theLists;   // The array of Lists
    int  currentSize;

    void rehashS( )
    {
        vector<list<HashedObjS> > oldLists = theLists;

            // Create new double-sized, empty table
        theLists.resize( nextPrime( 2 * theLists.size( ) ) );
        for( int j = 0; j < theLists.size( ); j++ )
            theLists[ j ].clear( );

            // Copy table over
        currentSize = 0;
        for( int i = 0; i < oldLists.size( ); i++ )
        {
            typename list<HashedObjS>::iterator itr = oldLists[ i ].begin( );
            while( itr != oldLists[ i ].end( ) )
                insertS( *itr++ );
        }
    }

    int myhashS( const HashedObjS & x ) const
    {
        int hashVal = hash( x );

        hashVal %= theLists.size( );
        if( hashVal < 0 )
            hashVal += theLists.size( );

        return hashVal;
    }
};



#endif
