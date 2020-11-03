#include <iostream>
#include <chrono>
#include "graph.h"

using namespace std;


int main() {
    
    string infile, start, outfile;
    
	// Initialize the empty graph
    graph g;

    // Get the input file
	cout << "Enter name of graph file: ";
    cin >> infile;
    
    // Build the graph based on the specified input file
    g.load(infile);
	
	// Get starting vertex
	do {
		cout << "Enter a valid ID for the starting vertex: ";
		cin >> start;
	} while (g.checkVertex(start) == false);
    
    // Start timer
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    
    // Find shortest path from specified start point to each other vertex
    g.dijkstra(start);
    
    // Stop timer
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
	chrono::duration<double> timeDiff = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "Total processing time (in seconds): " << timeDiff.count() << endl;
    
    // Get the output file
    cout << "Enter name of output file: ";
    cin >> outfile;
    
    g.show(outfile);
    
    return 1;
    
}