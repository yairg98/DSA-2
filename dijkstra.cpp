#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include <iterator>
#include <chrono>
#include "heap.h"

using namespace std;


// Single graph edge, stores destination vertex and weight
struct edge {
    string v1;
    string v2;
    int weight;
    edge(string a, string b, int w) : v1(a), v2(b), weight(w) {}
};


// Single graph vertex
struct vertex {
    string id; // may end up being uncessesary here
    list<edge> adj;
    bool known = false;
    int dist = -1;
    string path = ""; // previous vertex on shortest path
    vertex(string s) : id(s) {}
};


int main() {
    
    // Initialize variables
    hashTable vertices; // Efficiently lookup vertex from ID
    list<string> seen;
    string infile, outfile, start, line, v1, v2;
    int weight, size = 0;
    vertex *pv, *pv1, *pv2;
    
    // Get the input file
    cout << "Enter name of graph file: ";
    cin >> infile;
    ifstream input(infile);
    
    // Get starting vertex
    cout << "Enter a valid ID for the starting vertex: ";
    cin >> start;
    
    
    // Record all graph vertices edges    
    
    // Start timer
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    
    // Record each graph edge line-by-line
    while ( getline(input, line) ) {
		// Parse the line, identifying v1, v2, and weight of edge
        stringstream ss(line);
        ss >> v1 >> v2 >> weight;
        edge e = edge(v1, v2, weight);
        
        // If v1 hasn't been seen yet, create a vertex and record pointer pv
        if ( ! vertices.contains(v1) ) {
            pv = (vertex *)(new vertex(v1));
            vertices.insert(v1, pv);
            seen.push_back(v1);
            size++;
        }
        
        // Otherwise, retrieve pointer to vertex v1
        else { pv = ((vertex *)vertices.getPointer(v1)); }
        
        // Add edge e to v1's adjacency list
        pv->adj.push_back(e);
        
        // Create vertex v2 and add it to "seen" list, if it doesn't exist already
        if ( ! vertices.contains(v2) ) {
            pv = (vertex *)(new vertex(v2));
            vertices.insert(v2, pv);
            seen.push_back(v2);
            size++;
        }
	}
    
    
    // Search for all shortest paths using Dijkstra's Algorithm
    
    // Retrieve the starting vertex pointer
    pv = (vertex *) vertices.getPointer(start);
    pv->dist = 0;
    pv->known = true;
    pv->path = start;

    // Add each edge leaving the start-vertex to the frontier
    heap frontier = heap(size);
    list<edge> :: iterator it;
    for ( it = pv->adj.begin(); it != pv->adj.end(); it++ ) {
        pv2 = (vertex *) vertices.getPointer(it->v2);
        pv2->dist = it->weight;
        pv2->path = (pv->path) + ", " + it->v2;
        frontier.insert(it->v2, it->weight);        
    }
    
    string id; // ID of the most vertex returned by deleteMin
    int dist; // shortest known distance to that vertex
    int w; // Net distance to new frontier vertex
    
    while ( !frontier.deleteMin(&id, &dist) ) {
        pv = (vertex *) vertices.getPointer(id);
        pv->known = true;
        
        // Expand frontier to include adjacent edges to current vertex
        for ( it = pv->adj.begin(); it != pv->adj.end(); it++ ) {
            
            // Check if new vertex is already known
            pv1 = (vertex *) vertices.getPointer(it->v1);
            pv2 = (vertex *) vertices.getPointer(it->v2);
            if ( pv2->known == true ) {
                continue;
            }
            
            // Frontier vertex dist = dist up to previous vertex + edge weight
            w = dist + it->weight;
            
            // Try to insert to frontier
            if ( frontier.insert(it->v2, w) == 0 ) {
                pv2 = (vertex *) vertices.getPointer(it->v2);
                pv2->dist = w;
                pv2->path = (pv1->path) + ", " + it->v2;
            }
            
            // If vertex is already in frontier, compare/change dist and path
            else {
                pv2 = (vertex *) vertices.getPointer(it->v2);
                if (w < pv2->dist) {
                    pv2->dist = w;
                    pv2->path = (pv1->path) + ", " + it->v2;
                }
                frontier.setKey(it->v2, pv2->dist);
            }
        }
    }
    
    // Stop timer
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
	chrono::duration<double> timeDiff = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "Total processing time (in seconds): " << timeDiff.count() << endl;
        
    // Get the output file
    cout << "Enter name of output file: ";
    cin >> outfile;
    ofstream output(outfile);
    
    // Print each vertex and its shortest path to the output file
    list<string> :: iterator it2;
    for ( it2 = seen.begin(); it2 != seen.end(); it2++ ) {
        pv = (vertex *) vertices.getPointer(*it2);
        output << pv->id << ": " << pv->dist << " [" << pv->path << "]" << endl;
    }
}