#include <string>
#include <iostream>

using namespace std;

int checkMerge(string a, string b, string c)
{
	// Return true if all three strings are empty
	if ( (a == "") && (b == "") && (c == "") ) { return true; }
	
	// Return false if two of the three strings are empty
	else if ( (a == "") + (b == "") + (c == "") == 3) { return false; }
	
	bool merge = false;
	string c2 = c;
	
	// Check if first character of a is the same as first character of c
	if (a[0] == c[0]) {	merge = checkMerge(a.substr(1), b, c.substr(1)); }
	
	// Repeat for string b, if merge has not been confirmed yet
	if (b[0] == c2[0] && merge==false) { merge = checkMerge(a, b.substr(1), c.substr(1)); }
	
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