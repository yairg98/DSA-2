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

    test();
    
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
    // Check if heap is already empty
    if (filled == 0) {
        return 0;
    }
    // Remove the top element in the heap and percolate down
    else {
        data[0] = std::move( data[1] );
        data[1] = std::move( data[filled--] );
        percDown(1);
    }
    
    test();
    
    return 0;
}


// Move a key higher up in the tree, to its correct location.
int heap::percUp(int posCur)
{
    // Store new node in data[0] temporarily
    data[0] = std::move( data[posCur] );
    
    // Percolate up the tree
    while ( data[0].key < data[posCur/2].key ) {
        data[posCur] = std::move( data[posCur/2] );
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
    // Store node at placeholder data[0]
    data[0] = std::move( data[posCur] );
    
    // Percolate down the tree
    int child;
    for ( ; posCur*2 <= filled; posCur = child ) {
        child = posCur * 2;
        // Check which child is smaller
        if( child != filled && data[child+1] < data[child] ) {
            child++;
        }
        // Check whether child is smaller than parent
        if ( data[child] < data[0] ) {
            data[posCur] = std::move(  data[child] );
        }
        // Break if nodes placement is correct
        else {
            break;
        }
        
        return posCur;
    }
    return 0;
}


int heap::getPos(node *pn)
{
    return (pn - &data[0]);
}


int heap::test()
{
    for (auto i : data) {
        std::cout << i.id << ": " << i.key << std::endl;
    }
    
    return 0;
}