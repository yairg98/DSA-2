#include "hash.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <bits/stdc++.h>
#include <typeinfo>
#include <string>
using namespace std;


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
		//cout << "1. " << key << endl; // test
		++pos %= capacity;
	}
	
	// Return 1 if the key was already in the hash table
	if (data[pos].key == key) {
		// cout << "2. " << key << endl; // test
		return 1;
	}
	
	// Rehash if necessary; return 2 if rehash fails
	else if (capacity / (capacity-filled) >= 2) {
		// cout << "3. " << key << endl; // test
		// cout << "Capacity: " << capacity << endl;
		if (rehash() == false) {
			cout << "4. " << key << endl;
			return 2;
		}
		cout << "New capacity: " << capacity << endl;
	}
	
	// Insert new key at data[pos]
	data[pos].key = key;
	data[pos].isOccupied = true;
	data[pos].isDeleted = false;
	filled++;
	return 0;
}


// Return true is hashTable contains the given key; otherwise return false
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


// Hash function
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
		if (data[pos].key == key) { return pos; }
		++pos %= capacity;
	}
	
	// If the key is not found
	return -1;
}


bool hashTable::rehash()
{
	// Back up all current data to backup vector and erase contents of original data vector
	vector<hashItem> backup = data;
	for (auto i : data) {
		i.isOccupied = false;
		i.isDeleted = false;
		i.key = "";
	}
	
	// Adjust capacity and resize the data vector
	capacity = getPrime(capacity);
	
	try { data.resize(capacity); }
	catch (std::bad_alloc) { 
		cout << "REHASH FAILED" << endl;
		return false;
	}
	
	
	// Restore data from backup
	for (auto i : backup) {
		if (i.key != "") { insert(i.key); }
	}
	
	return true;
}


// Return the first prime number from the list larger than "size"
unsigned int hashTable::getPrime(int size)
{
	// Precalculated list of primes ranging from ~1,000 to ~4,000,000
	static int primes[] = {1009, 2003, 4001, 16001, 32003, 64007, 128021, 256019, 512009, 1024021, 2048003, 4096013};
	
	for (int i : primes) {
		if (i > size) { return i; }
	}
	return primes[11];
}


void hashTable::test()
{
	string str = "inroad";
	for (auto i : data) {
		if (i.key != "") {
			// for (int j=0; j<str.length() && j<i.key.length(); j++) {
				// cout << (i.key[j]==str[j]) << endl;
			// }
			cout << i.key << endl;
			cout << (i.key == str) << endl;
		}
	}
}

