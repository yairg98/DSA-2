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
    // Find the correct node using the hashtable
    int pos = getPos((node *)mapping.getPointer(id));
    
    data[pos].key = key;
    percUp(pos);
    percDown(pos);
    
    test();
    
    return 0;
}


// Remove item from heap.
int heap::remove(const std::string &id, int *key)
{
    // Find the correct node using the hashtable
    int pos = getPos((node *)mapping.getPointer(id));
    
    // Remove that node and percolate down
    mapping.remove(data[pos].id);
    data[pos] = data[filled--];
    data[filled+1] = node();
    percDown(pos);
    
    test();
    
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
        node min = data[1];
        mapping.remove(min.id);
        data[1] = data[filled--];
        data[filled+1] = node();
        percDown(1);
    }
    
    test();
    
    return 0;
}


// Move a key higher up in the tree, to its correct location.
int heap::percUp(int posCur)
{
    // Store new node in data[0] temporarily
    data[0] = data[posCur];
    
    // Percolate up the tree
    while ( data[0] < data[posCur/2] ) {
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
    // Store node at placeholder data[0]
    data[0] = data[posCur];
    
    // Percolate down the tree
    int child;
    for ( ; posCur*2 <= filled; posCur = child ) {
        
        // Consider left child
        child = posCur * 2;
        
        // Choose smaller of left and right children
        if( child != filled && data[child+1] < data[child] ) {
            child++;
        }
        
        // Check whether child is smaller than parent
        if ( data[child] < data[0] ) {
            data[posCur] = data[child];
            mapping.setPointer(data[posCur].id, &data[posCur]);
        }
        
        // Break if nodes placement is correct
        else {
            break;
        }
    }
    data[posCur] = data[0];
    mapping.setPointer(data[posCur].id, &data[posCur]);
    data[0] = node();
    
    return posCur;
}


int heap::getPos(node *pn)
{
    return (pn - &data[0]);
}


int heap::test()
{
    /* 
    for (int i=0; i<=filled; i++) {
        std::cout << data[i].id << ": " << data[i].key << std::endl;
    }
     */
    return 1;
}