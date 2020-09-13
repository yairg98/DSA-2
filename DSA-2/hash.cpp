#include "hash.h"
#include <iostream>
#include <fstream>
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
	while ( data[pos].isOccupied && data[pos].key != key) {
		++pos %= capacity;
	}
	
	// Return 1 if the key was already in the hash table
	if (data[pos].key == key) {
		return 1;
	}
	
	// Rehash if necessary; return 2 if rehash fails
	else if (capacity/filled == 1) {
		if (rehash() == false) {
			return 2;
		}
	}
	
	// Insert new key at data[pos]
	data[pos].key = key;
	data[pos].isOccupied = true;
	data[pos].isDeleted = false;
	return 0;
}


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


// Return true is hashTable contains the given key; otherwise return false
bool hashTable::contains(const std::string &key) 
{
	return (findPos(key) == -1) ? false : true; 
}


unsigned int hashTable::getPrime(int size)
{
	// Precalculated list of primes ranging from ~1,000 to ~4,000,000
	static int primes[] = {1009, 2003, 4001, 16001, 32003, 64007, 128021, 256019, 512009, 1024021, 2048003, 4096013};
	
	// Find first prime larger than "size"
	int start = 0; 
	int end = sizeof(primes)/sizeof(primes[0]);
	int mid = (start + end) / 2;
    while (start <= end) 
    { 
        mid = (start + end) / 2;
		// Move right
        if (primes[mid] <= size) { start = mid + 1; }
        // Move left
        else { end = mid - 1; }
    } 
    return mid;
}


