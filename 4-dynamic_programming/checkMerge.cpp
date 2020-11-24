#include <string>
#include <iostream>
#include<bits/stdc++.h> 

using namespace std;

string checkMerge(string a, string b, string c)
{
	// Return true if all three strings are empty
	if ( (a == "") && (b == "") && (c == "") ) { return ""; }
	
	// Return false if two of the three strings are empty
	else if ( (a == "") + (b == "") + (c == "") == 3) { return "*** NOT A MERGE ***"; }
	
	// Default return value
	string merge = "*** NOT A MERGE ***";
	
	// Check if first character of a is the same as first character of c
	if (a[0] == c[0]) {
		merge = checkMerge(a.substr(1), b, c.substr(1));
	}
	
	// If merge was confirmed, construct output string
	if (merge != "*** NOT A MERGE ***") {
		merge.insert(0, string(1,toupper(c[0])));
	}
	
	// Repeat for string b, if merge has not been confirmed yet
	else if (b[0] == c[0]){
		merge = checkMerge(a, b.substr(1), c.substr(1));
		merge.insert(0, string(1,c[0]));
	}
	
	return merge;
	
}


int main()
{
	string a, b, c;
	
	cout << "String a: ";
	cin >> a;
	
	cout << "String b: ";
	cin >> b;
	
	cout << "String c: ";
	cin >> c;
	
	cout << checkMerge(a, b, c) << endl;
	
}