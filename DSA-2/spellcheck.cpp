#include "hash.cpp"


hashTable loadDictionary(string dict_file)
{	
	// Open dictionary file input stream
	ifstream input(dict_file);
	
	string entry;
	
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


void spellChecker(string input_file, string output_file)
{
	// Open spellchecker file input/output streams
	ifstream input(input_file);
	ofstream output(output_file);
}


int main() 
{
	string dict_file;
	string input_file;
	string output_file;
	
	
	// User enters input file name
	cout << "Dictionary file: " << endl;
	cin >> dict_file;
	
	// User enters input file name
	cout << "Input file: " << endl;
	cin >> input_file;

	// User enters output file name
	cout << "Output file: " << endl;
	cin >> output_file;
	
	hashTable dict = loadDictionary(dict_file);
	
}