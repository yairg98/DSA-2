#include "hash.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include<bits/stdc++.h>
#include <cstring>

using namespace std;

int main()
{
	string s[] = { "a", "abc", "HellowWorld", "MissionImpossible", "???", "if", "in", "it", "is", "aaple" };
	cout << s << endl;
	
	long val = 0;	
	int hash = 0;
	int base = 0;
	int exp = 0;
	
	for (int j=0; j < sizeof(s)/sizeof(s[0]); j++) {	
		transform(s[j].begin(), s[j].end(), s[j].begin(), ::tolower);
		cout << s[j] << endl;
		for (int i=0; i < s[j].length(); i++) {
			base = 30 - ( int(s[j][i]) % 26 );
			exp = 10-(i%5);
			val = pow(base, exp) + int(s[j][i]);
			hash = (hash + val) % 2048003;
		}
		cout << hash << endl;
	}
}