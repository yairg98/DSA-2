#include "hash.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include<bits/stdc++.h>
#include <cstring>

using namespace std;


// Use folding on a string, summed 4 bytes at a time
// https://opendsa-server.cs.vt.edu/ODSA/Books/CS3/html/HashFuncExamp.html
int sfold(string s, int M) {
  long sum = 0, mul = 1;
  for (int i = 0; i < s.length(); i++) {
    mul = (i % 4 == 0) ? 1 : mul * 256;
    sum += tolower(s[i]) * mul;
  }
  return (int)(abs(sum) % M);
}


int main()
{
	string s[] = { "a", "abc", "HellowWorld", "MissionImpossible", "???", "if", "in", "it", "is", "aaple", "ape", "hello", "on", "no" };
	
	int hash = 0;
	int capacity = 16001;
	
	for (string str : s) {	
		// transform(str.begin(), str.end(), str.begin(), ::tolower);
		// cout << str << endl;
		
		hash = sfold(str, capacity);
		
		cout << hash << endl;
	}
}