# include "heap.h"
#include <string>
#include <iostream>


// Constructor to initialize hashTable with chosen capacity
heap::heap( int capacity ) : mapping(capacity*2)
{
    data.resize(capacity+1);
}


// Insert the goven string and key to the heap.
int heap::insert(const std::string &id, int key)
{
    int pos = filled+1;
    data[pos].id = id;
    data[pos].key = key;
    pos = percUp(pos);
    filled++;
    
    return 0;
}


// Change the key of an existing entry.
int heap::setKey(const std::string &id, int key)
{
    return 0;
}


// Remove item from heap.
int heap::remove(const std::string &id, int *key)
{
    return 0;
}


// Remove top item from heap
int heap::deleteMin(const std::string *id, int *key)
{
    return 0;
}


// Move a key higher up in the tree, to its correct location.
int heap::percUp(int posCur)
{
    // Store new node in data[0] temporarily
    data[0] = data[posCur];
    
    // Percolate up the tree
    while ( data[0].key < data[posCur/2].key ) {
        data[posCur] = data[posCur/2];
        mapping.setPointer(data[posCur].id, &data[posCur]);
        posCur /= 2;
    }
    
    // Insert new node at correct position and clear placeholder
    data[posCur] = data[0];
    mapping.insert(data[posCur].id, &data[posCur]);
    data[0] = node();
    
    // Return the position of the new node
    return posCur;
}


// Move a key down the tree, to its correct location
int heap::percDown(int posCur)
{
    return 0;
}


int heap::getPos(node *pn)
{
    int pos = pn - &data[0];
    return pos;
}