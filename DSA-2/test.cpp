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


// https://opendsa-server.cs.vt.edu/ODSA/Books/CS3/html/HashFuncExamp.html
int sfold(string s, int M) {
  long sum = 0, mul = 1;
  for (int i = 0; i < s.length(); i++) {
    mul = (i % 4 == 0) ? 1 : mul * 256;
    sum += tolower(s[i]) * mul;
  }
  return (int)(abs(sum) % M);
}



void test(int id)
{
	// clock_t t1 = clock();
	
	bool b;
	for (int i=0; i < 10; i++) {
		cout << id << ": " << i << endl;
		// this_thread::sleep_for(chrono::milliseconds(10));
		for (long x=0; x<100000000; x++) { x%2==0 ? true : false; }
	}
	
	// clock_t t2 = clock();
	// double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
	
	// cout <<  id << " Thread time: " << timeDiff << endl;
}


int main()
{
	cout << "Available threads: " << std::thread::hardware_concurrency() << endl;
	
	clock_t t1 = clock();
	
	int i = 0;
	vector<std::thread> all_threads;
	while ( i < thread::hardware_concurrency()/2 ) {
		all_threads.push_back(thread(test, i));
		i++;
	}
	
	for (thread & t : all_threads) {
		t.join();
	}
	// std::thread first(test, "First - ");
	// std::thread secnd(test, "Secnd - ");
	
	// first.join();
	// secnd.join();
	
	clock_t t2 = clock();
	double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
	
	cout << "Total time: " << timeDiff << endl;
}