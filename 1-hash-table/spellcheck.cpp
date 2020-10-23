#include <string>
#include <iostream>
#include <fstream>
#include "hash.h"
#include <bits/stdc++.h>
#include <chrono>
using namespace std;


// Load each word of named dictionary file into dict hash table, return 
hashTable loadDictionary(string &dict_file)
{	
	// Open dictionary file input stream
	ifstream input(dict_file);
	string entry;
	
/* 	// Count lines of dict to initialize hash table with appropriate size (size*2)
	int size = 0;
	while ( getline(input, entry) ) {
		size++;
	} */
	
	// Initialize hash table and add each dictionary entry
	// Assumption: typical dictionary countains 50,000 words
	hashTable dict = hashTable(100000); 
	input.clear();
	input.seekg(0); // Return pointer to first line
	while ( getline(input, entry) ) {
		transform(entry.begin(), entry.end(), entry.begin(), ::tolower);
		dict.insert(entry);
	}
	
	return dict;
}


// Check if a word is valid
bool checkWord(string &word, hashTable &dict)
{
	// Return true if the word is empty or in the dictionary
	return word=="" ? true : dict.contains(word);
}


// Spellcheck an individual line of a file
void checkLine(string &line, int num, hashTable &dict, ofstream &output)
{
	// Conert all characters to lowercase (spellchecker is case insensitive)
	transform(line.begin(), line.end(), line.begin(), ::tolower);
	
	// Add trailing space to signal the end of the last word on the line
	line.append(" ");

	// Track the current word
	string word = "";
	bool numerical = false;
	
	// Iterate through the line letter by letter
	for (int i=0; i<line.length(); i++) {
		
		// Add non-numerical character to "word"
		if ( (line[i] >= 97 && line[i] <= 122) || (line[i] == 45) || (line[i] == 39) ) { 
			word += line[i];
		}
		
		// Add numerical character to "word"
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
			
			// Check if word is numerical or in dictionary
			else if ( numerical == false && checkWord(word, dict) == false ) {
				output << "Unknown word at line " << to_string(num) << ": " << word << endl;
			}
			
			// Reset "word"
			word = "";
			numerical = false;
		}
	}
}


// Spellcheck the named input file. Print results to named output file.
void spellChecker(string &infile, string &outfile, hashTable &dict)
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


// Prompt user for dictionary, input file, and output file - perform spellcheck
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
	
	// Load the dictionary and print the processing
	chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
	hashTable dict = loadDictionary(dict_file);
	chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
	chrono::duration<double> timeDiff = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
	cout << "Time to load dictionary: " << timeDiff.count() << endl;
	
	// Spellcheck the input file and print the processing time
	t1 = chrono::steady_clock::now();
	spellChecker(infile, outfile, dict);
	t2 = chrono::steady_clock::now();
	timeDiff = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
	cout << "Time to spellcheck document: " << timeDiff.count() << endl;
}