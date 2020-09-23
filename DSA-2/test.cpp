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
	chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
	
	bool b;
	for (int i=0; i < 10; i++) {
		// this_thread::sleep_for(chrono::milliseconds(10));
		for (long x=0; x<100000000; x++) { x%2==0 ? true : false; }
	}
	
	chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
	chrono::duration<double> timeDiff = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
	
	cout <<  id << " Thread time: " << timeDiff.count() << endl;
}


int main()
{
	cout << "Available threads: " << std::thread::hardware_concurrency() << endl;
	
	for (int n=1 n<=thread::hardware_concurrency(); n++) {
		cout << "\n********  " << n << "  ********" << endl;
			
		chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
		
		int i = 0;
		vector<std::thread> all_threads;
		while ( i < n ) { // thread::hardware_concurrency()
			all_threads.push_back(thread(test, i));
			i++;
		}
		
		for (thread & t : all_threads) {
			t.join();
		}
		
		chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
		chrono::duration<double> timeDiff = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
		
		
		cout << "Total time: " << timeDiff.count() << endl;
	}
}