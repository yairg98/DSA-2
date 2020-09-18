#include "hash.cpp"


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
	hashTable dict = hashTable(size*2);
	input.clear();
	input.seekg(0); // Return pointer to first line
	while ( getline(input, entry) ) {
		transform(entry.begin(), entry.end(), entry.begin(), ::tolower);
		dict.insert(entry);
	}
	
	return dict;
}


bool checkWord(string word, hashTable dict)
{	
	// Possibly unnecessary to check for empty word
	return word=="" ? true : dict.contains(word);
}


void checkLine(string line, int num, hashTable dict, ofstream &outfile)
{
	transform(line.begin(), line.end(), line.begin(), ::tolower);

	string word = "";
	bool numerical = false;
	
	for (int i=0; i<line.length(); i++) {
		
		// Add non-numerical character
		if ( (line[i] >= 96 && line[i] <= 122) || (line[i] == 45)) { 
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
				outfile << "Long word at line " << to_string(num) << ", starts: " << word.substr(0,20) << endl;
			}
			
			// Check if word is not numerical or in dictionary
			else if ( numerical == false && checkWord(word, dict) == false ) {
				outfile << "Unknown word at line " << to_string(num) << ": " << word << endl;
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
	hashTable dict = loadDictionary(dict_file);
	
	// Check the input file
	spellChecker(infile, outfile, dict);
	
	dict.test();
	
}