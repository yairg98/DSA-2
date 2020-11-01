#include <fstream>
#include <sstream>
#include <list>
#include <iterator>
#include "heap.h"

using namespace std;


class graph {

private:
    
    hashTable vertices; // Efficiently lookup vertex from ID
    list<string> seen; // Track all previously seen vertices in original order
    int size = 0;
    
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
    
    
public:

    // Build the graph from the given file
    void load(string infile);
	
	
	// Check the validity of given vertex
	bool checkVertex(string v);
    
    
    // Run Dijkstra's algorithm to find the shortest path to each vertex
    void dijkstra(string start);
    
    
    // Iterate through vertices in order and print shortest paths
    void show(string outfile);    
    
};