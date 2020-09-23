#include <string>
#include <iostream>
#include <fstream>
#include "hash.h"
#include <bits/stdc++.h>
#include <chrono>
#include <ctime>
using namespace std;

hashTable loadDictionary(string dict_file)
{	
	// Open dictionary file input stream
	ifstream input(dict_file);
	
	string entry;
	string prev;
	
	// Count lines of dict to initialize hash table with correct size
	int size = 0;
	while ( getline(input, entry) ) {
		size++;
	}
	
	// Initialize hash table and add each dictionary entry
	hashTable dict = hashTable(49000);
	input.clear();
	input.seekg(0); // Return pointer to first line
	while ( getline(input, entry) ) {
		transform(entry.begin(), entry.end(), entry.begin(), ::tolower);
		dict.insert(entry);
	}
	
	return dict;
}


bool checkWord(string word, hashTable &dict)
{	
	// Possibly unnecessary to check for empty word
	return word=="" ? true : dict.contains(word);
}


void checkLine(string &line, int num, hashTable &dict, ofstream &output)
{
	transform(line.begin(), line.end(), line.begin(), ::tolower);
	line.append(" ");

	string word = "";
	bool numerical = false;
	
	for (int i=0; i<line.length(); i++) {
		
		// Add non-numerical character
		if ( (line[i] >= 97 && line[i] <= 122) || (line[i] == 45) || (line[i] == 39) ) { 
			word += line[i];
		}
		
		// Add numerical character
		else if ( line[i] >= 48 && line[i] <= 57 ) {
			numerical = true;
			word += line[i];
		}
		
		// Reached end of word
		else {
			
			// Check if word is too long
			if ( word.length() > 20 ) {
				output << "Long word at line " << to_string(num) << ", starts: " << word.substr(0,20) << endl;
			}
			
			// Check if word is not numerical or in dictionary
			else if ( numerical == false && checkWord(word, dict) == false ) {
				output << "Unknown word at line " << to_string(num) << ": " << word << endl;
			}
			
			word = "";
			numerical = false;
		}
	}
}


void spellChecker(string infile, string outfile, hashTable dict)
{
	// Open spellchecker file input/output streams
	ifstream input(infile);
	ofstream output(outfile);
	
	// Check one line at a time
	string line;
	string out;
	int num = 1;
	while ( getline(input, line) ) {
		checkLine(line, num, dict, output);
		num++;
	}
}


int main() 
{
	string dict_file;
	string infile;
	string outfile;
	
	// User enters input file name
	cout << "Dictionary file: " << endl;
	cin >> dict_file;
	
	// User enters input file name
	cout << "Input file: " << endl;
	cin >> infile;

	// User enters output file name
	cout << "Output file: " << endl;
	cin >> outfile;
	
	// Load the dictionary
	chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
	hashTable dict = loadDictionary(dict_file);
	chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
	chrono::duration<double> timeDiff = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
	cout << "Time to load dictionary: " << timeDiff.count() << endl;
	
	// Check the input file
	t1 = chrono::steady_clock::now();
	spellChecker(infile, outfile, dict);
	t2 = chrono::steady_clock::now();
	timeDiff = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
	cout << "Time to spellcheck document: " << timeDiff.count() << endl;
	
	
	// dict.test();
	
}