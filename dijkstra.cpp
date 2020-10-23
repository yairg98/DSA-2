#include <fstream>
#include <iostream>
#include <sstream>
#include "heap.h"

using namespace std;


// Single graph edge, stores destination vertex and weight
struct edge {
    string v2;
    int weight;
    edge(string v, int w) : v2(v), weight(w) {}
};


// Single graph vertex
struct vertex {
    string id; // may end up being uncessesary here
    vector<edge> adj;
    bool known = false;
    int dist = 0;
    vertex(string s) : id(s) {}
};


int main() {
    
    // Record all graph vertices edges
    
    // Initialize variables
    hashTable vertices;
    string infile, line, v1, v2;
    int weight;
    vertex *pv;
    
    // Get the input file
    cout << "Enter name of graph file: " << endl;
    cin >> infile;
    ifstream input(infile);
    
    // Record each graph edge line-by-line
    while ( getline(input, line) ) {
		stringstream ss(line);
        ss >> v1 >> v2 >> weight;
        edge e = edge(v2, weight);
        
        // Create vertex v1, if it doesn't exist already
        if ( ! vertices.contains(v1) ) {
            pv = (vertex *)(new vertex(v1));
            vertices.insert(v1, pv);
        }
        
        // Otherwise, retrieve pointer to vertex v1
        else { pv = ((vertex *)vertices.getPointer(v1)); }
        
        // Add edge e to v1 adjacency list
        pv->adj.push_back(e);
	}
    
    cout << "Loaded" << endl;
    
    vertices.test();
    
}