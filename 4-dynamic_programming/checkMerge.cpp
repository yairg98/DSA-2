#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <bits/stdc++.h>
#include <chrono>

using namespace std;


// Record all previously-seen instances
unordered_map<string, string> memory;

string checkMerge(string a, string b, string c)
{
	// Return true if all three strings are empty
	if ( (a == "") && (b == "") && (c == "") ) { return ""; }
	
	// Return false if two of the three strings are empty
	else if ( (a == "") + (b == "") + (c == "") == 2) { return "*** NOT A MERGE ***"; }
	
	// Check if scenario is already in memory
	else if (memory.find(a+"\n"+b+"\n"+c) != memory.end()) { return memory[a+"\n"+b+"\n"+c]; }
	
	// Default return value
	string merge = "*** NOT A MERGE ***";
	
	// Check if first character of a is the same as first character of c
	if ( (a != "") && (a[0] == c[0]) ) {
		merge = checkMerge(a.substr(1), b, c.substr(1));
		// If merge was confirmed, construct output string
		if (merge != "*** NOT A MERGE ***") {
			merge.insert(0, string(1,toupper(c[0])));
		}
	}
	
	// Repeat for string b, if merge has not been confirmed yet
	if ( (b != "") && (b[0] == c[0]) && (merge == "*** NOT A MERGE ***") ){
		merge = checkMerge(a, b.substr(1), c.substr(1));
		// If merge was confirmed, construct output string
		if (merge != "*** NOT A MERGE ***") {		
			merge.insert(0, string(1,c[0]));
		}	
	}
	
	// Add scenario and result to memory
	memory.insert(make_pair(a+"\n"+b+"\n"+c, merge));
	
	return merge;
}


int main()
{
	string infile, outfile, a, b, c;
	
	// Get the input file
	cout << "Enter name of input file: ";
    cin >> infile;
	ifstream input(infile);
	
	// Get the output file
    cout << "Enter name of output file: ";
    cin >> outfile;
	ofstream output(outfile);
	
	// Initialize start/stop timer variables
	// chrono::steady_clock::time_point t1, t2;
	// chrono::duration<double> timeDiff;
	// int n = 0;
	
	// Read lines three at a time, and print checkMerge results to output file
	while (getline(input, a) && getline(input, b) && getline(input, c)) {
		// t1 = chrono::steady_clock::now();
		output << checkMerge(a,b,c) << endl;
		// t2 = chrono::steady_clock::now();
		// timeDiff = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
		// cout << "-- " << ++n << " --" << endl;
		// cout << "Time (seconds): " << timeDiff.count() << endl;
		memory.clear();
	}
	
}