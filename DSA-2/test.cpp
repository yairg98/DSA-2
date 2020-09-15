#include "hash.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include<bits/stdc++.h>
#include <cstring>
#include <thread>
#include <chrono>
#include <ctime>


using namespace std;


// Use folding on a string, summed 4 bytes at a time
// https://opendsa-server.cs.vt.edu/ODSA/Books/CS3/html/HashFuncExamp.html
// int sfold(string s, int M) {
  // long sum = 0, mul = 1;
  // for (int i = 0; i < s.length(); i++) {
    // mul = (i % 4 == 0) ? 1 : mul * 256;
    // sum += s[i] * mul;
  // }
  // return (int)(abs(sum) % M);
// }


void test(string id)
{
	clock_t t1 = clock();
	
	bool b;
	for (int i=0; i < 10; i++) {
		cout << id << i << endl;
		// this_thread::sleep_for(chrono::milliseconds(10));
		for (long x=0; x<500000000; x++) { x%2==0 ? true : false; }
	}
	
	clock_t t2 = clock();
	double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
	
	cout << "Thread time: " << id << timeDiff << endl;
}


int main()
{
	cout << "Available threads: " << std::thread::hardware_concurrency() << endl;
	
	clock_t t1 = clock();
	
	std::thread first(test, "First - ");
	std::thread secnd(test, "Secnd - ");
	
	first.join();
	secnd.join();
	
	clock_t t2 = clock();
	double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
	
	cout << "Total time: " << timeDiff << endl;
}