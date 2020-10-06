#include "hash.h"
#include <iostream>
#include <cmath>
#include <typeinfo>
#include <string>
using namespace std;


// Constructor to initialize hashTable with chosen capacity ("size")
hashTable::hashTable( int size )
    {
        capacity = getPrime(size);
        data.resize(capacity);
        filled = 0;
    }


// Insert new value to hash table (returns 0:success, 1:key already present, 2: rehash failed)
int hashTable::insert(const std::string &key, void *pv)
{   
    // Generate position value from hash function
    int pos = hash(key);
    
    // Search for location of key (if already inserted) or 1st available spot
    while ( data[pos].isOccupied && (data[pos].key != key)) {
        ++pos %= capacity;
    }
    
    // Return 1 if the key was already in the hash table
    if ( (data[pos].key == key) && (data[pos].isDeleted == false) ) { 
        return 1;
    }
    
    // Rehash when more than half the hashTable capacity is filled
    else if (capacity / (capacity-filled) >= 2) {
        // Attempt rehash; return 2 in case of failure
        if (rehash() == false) { return 2; }
    }
    
    // Insert new key at data[pos]
    data[pos].key = key;
    data[pos].pv = pv;
    data[pos].isOccupied = true;
    data[pos].isDeleted = false;
    filled++;
    return 0;
}


// Return true if hashTable contains the given key; otherwise return false
bool hashTable::contains(const std::string &key) 
{
    return (findPos(key) == -1) ? false : true; 
}


// Delete item from hash table; return true/false for success/failure
bool hashTable::remove(const std::string &key)
{
    int pos = findPos(key);
    if (pos == -1) { return false; }
    else {
        data[pos].isOccupied = false;
        data[pos].isDeleted = true;
        return true;
    }
}


// Retrieve the pointer stored in the hashItem with the given key
void *hashTable::getPointer(const std::string &key, bool *b)
{
    int pos = findPos(key);
    
    // Set indicator to true if item was found, false if not found
    if ( b != NULL ) { *b = (pos != -1); }
    
    // If key is not found, return null pointer
    if ( pos == -1 ) { return nullptr; }
    
    // Otherwise return the pointer associated with the key
    else { return data[pos].pv; }
}


// Store the given pointer in the hashItem with the given key
int hashTable::setPointer(const std::string &key, void *pv)
{
    int pos = findPos(key);
    // Check if key is in the table
    if ( pos == -1 ) { return 1; }
    data[pos].pv = pv;
    return 0;
}


// Hash function - given a string, return a numerrcal hash value
// Source: https://opendsa-server.cs.vt.edu/ODSA/Books/CS3/html/HashFuncExamp.html
int hashTable::hash(const std::string &key)
{
    long sum = 0, mul = 1;
    for (int i = 0; i < key.length(); i++) {
        mul = (i % 8 == 0) ? 1 : mul * 256;
        sum += tolower(key[i]) * mul; // Note: conversion to lowercase
    }
    return (int)(abs(sum) % capacity);
}


// Return the position of the given key, or -1 if not found
int hashTable::findPos(const std::string &key)
{
    // Search for key
    int pos = hash(key);
    while ( data[pos].isOccupied || data[pos].isDeleted) {
        if (data[pos].key == key) { 
            return ( data[pos].isDeleted ? -1 : pos );
        }
        ++pos %= capacity;
    }
    
    // If the key is not found
    return -1;
}


// Expland the hashTable capacity and rehash all current data accordinglgy
bool hashTable::rehash()
{
    // create backup vector, and fnd new data capacity
    int new_cap = getPrime(capacity);
    vector<hashItem> backup;
    data.swap(backup);
    
    //
    try { data.resize(new_cap); }// Adjust data vector to the new size
    catch (std::bad_alloc) {
        cout << "REHASH FAILED" << endl;
        return false;
    }
    
    capacity = new_cap;
    filled = 0;
    
    for (auto i : backup) {
        if ( (i.isOccupied == true) && (i.isDeleted == false) ) {
            insert(i.key);
        }
    }
    return true;
}


// Return the first prime number from the list larger than given "size"
unsigned int hashTable::getPrime(int size)
{
    // Precalculated list of primes ranging from ~1,000 to ~4,000,000
    static int primes[] = {1009, 2003, 4001, 16001, 32003, 64007, 128021, 256019, 512009, 1024021, 2048003, 4096013};
    
    // Not the most efficient, but it's such a short list that it does not matter
    // Assumes the list to be sorted
    for (int i : primes) {
        if (i > size) { return i; }
    }
    
    // If the list is maxed out, just return the largest value (last)
    return primes[11];
}


// Ignore - public wrapper for easy testing of private hashTable functions, etc.
void hashTable::test()
{   
    for (auto i : data) {
        if ( i.key != "" && i.isDeleted == false ) {
            cout << "\n" << i.key << endl;
            cout << "Pointer -> " << (i.pv!=nullptr) << endl;
        }
    }
}