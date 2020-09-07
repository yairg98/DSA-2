/*

Yair Andrew Gross
DSA1 - Programming Project #1
11/26/2019

This program implements and tests Stack and Queue classes.
See the assignment document for more detail.

*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>


// Stack and queue classes will be based on the abstract SimpleList class
template <class T>
class SimpleList
{
private:

	// Nested Node class used to build basic singly-linked list
	class Node
	{
	private:
		T data;
		Node *next;
	public:
		// Node constructor
		Node(T new_data = 0, Node *new_next = nullptr) :
			data{new_data}, next{new_next} {}

		// Retrieve data stored in node
		T get_data()
		{
			return data;
		}

		// Store data in node
		void set_data(T new_data)
		{
			data = new_data;
		}

		// Retrieve pointer to next node
		Node* get_next()
		{
			return next;
		}

		// Set next node
		void set_next(Node *new_next)
		{
			next = new_next;
		}
	};

	// Data members - first and last nodes of singly-linked list
	int size;
	Node *first; // not pointed to by any other nodes
	Node *last; // does not point to any other nodes

public:
	// SimpleList Constructor
	SimpleList() : size{0}, first{nullptr}, last{nullptr} {}

	// Return the current size of the list
	int get_size()
	{
		return size;
	}

	// Pop the first node - same for both stacks and queues
	T pop()
	{
		Node *popped_node = first;
		first = first->get_next();
		T popped_data = popped_node->get_data();
		delete popped_node;
		popped_node = nullptr;
		if (size == 1) {
			last = nullptr;
		}
		size = size - 1;
		return popped_data;
	}

	// virtual push function to be implemented differently for stacks and queues
	virtual void push(T) = 0;

	// stack implementatioin of push - add new node to beginning
	void push_stack(T push_data)
	{
		Node *new_node = new Node(push_data, first);
		first = new_node;
		new_node = nullptr;
		size = size + 1;
	}

	// Queue implementation of push - add new node to end
	void push_queue(T push_data)
	{
		Node *new_node = new Node(push_data, first);
		if (size == 0) {
			first = new_node;
		}
		else {
			last->set_next(new_node);
		}
		last = new_node;
		size = size + 1;
	}
};


// Create Queue class (derived from SimpleList)
template <class T>
class Queue : public SimpleList<T>
{
public:
	// Replace virtual "push" function with appropriate version
	void push(T push_data)
	{
		this->push_queue(push_data);
	}
};

// Create Stack class (derived from SimpleList)
template <class T>
class Stack : public SimpleList<T>
{
public:
	// Replace virtual "push" function with appropriate version
	void push(T push_data)
	{
		this->push_stack(push_data);
	}
};

int main()
{

	// Initialize maps to keep track of existing stacks and queues
	std::map<std::string, SimpleList<int>* > imap;
	std::map<std::string, SimpleList<double>* > dmap;
	std::map<std::string, SimpleList<std::string>* > smap;

	// Initialize input_file and output_file (maximum of 50 characters each)
	std::string input_file;
	std::string output_file;

	// Initialize command (whole and as individual words)
	std::string command;
	std::string operation; // first word of the command
	std::string list_name; // second word of the command
	std::string value; // third word of the command


	// User enters input file name
	std::cout << "Input file: " << '\n';
	std::cin >> input_file;
	std::ifstream input(input_file);

	// User enters output file name
	std::cout << "Output file: " << '\n';
	std::cin >> output_file;
	std::ofstream output(output_file);


	// Read and process each line of the input file
	// Line format: "operation" "list_name" ["value"] -> see assignment document for examples
	while (std::getline(input, command)) {

		// Print the following, per the assignmen guidelines
		output << "PROCESSING COMMAND: " << command << '\n';

		// Split command into its separate words:
		
		// Find first word ("operation")
		operation = command.substr(0, command.find(" "));
		command.erase(0, operation.length() + 1);

		// Find second word ("list_name")
		list_name = command.substr(0, command.find(" "));

		// Find third word ("value")
		if (operation == "create" || operation == "push") {
			command.erase(0, list_name.length() + 1);
			value = command;
		}
		// Do not look for third word if command starts with "pop"
		else {
			value = "";
		}

		// Process the command
		
		// Process "create" command
		if (operation == "create") {

			// Check for/create list of type int
			if(list_name[0] == 'i') {
				// Check if list by this name exists already
				if (imap.find(list_name) == imap.end()) {
					// create new list with this name
					if (value == "stack") {
						// Add new stack to map (or a pointer to the stack)
						imap.insert(
						std::pair<std::string,
						Stack<int>*>(list_name, new Stack<int>)
						);
					}
					else {
						// Add new queue to map (or a pointer to the queue)
						imap.insert(
						std::pair<std::string,
						Queue<int>*>(list_name, new Queue<int>)
						);
					}
				}
				else {
					// If list by this name already exists
					output << "ERROR: This name already exists!" << '\n';
				}
			}
			// Check for/create list of type double
			else if (list_name[0] == 'd') {
				// Check if list by this name exists already
				if (dmap.find(list_name) == dmap.end()) {
					// create new list by this name
					if (value == "stack") {
						// Add new stack to map (or a pointer to the stack)
						dmap.insert(
						std::pair<std::string,
						Stack<double>*>(list_name, new Stack<double>)
						);
					}
					else {
						// Add new queue to map (or a pointer to the queue)
						dmap.insert(
						std::pair<std::string,
						Queue<double>*>(list_name, new Queue<double>)
						);
					}
				}
				else {
					// List by this name already exists
					output << "ERROR: This name already exists!" << '\n';
				}
			}

			// Check for/create list of type string
			else if (list_name[0] == 's') {
				// Check if list by this name exists already
				if (smap.find(list_name) == smap.end()) {
					//Does NOT exist yet - create new list by this name
					if (value == "stack") {
						// Add new stack to map (or a pointer to the stack)
						smap.insert(
						std::pair<std::string,
						Stack<std::string>*>(list_name, new Stack<std::string>)
						);
					}
					else {
						// Add new queue to map (or a pointer to the queue)
						smap.insert(
						std::pair<std::string,
						Queue<std::string>*>(list_name, new Queue<std::string>)
						);
					}
				}
				else {
					// List by this name already exists
					output << "ERROR: This name already exists!" << '\n';
				}
			}
    }

		// Process "push" command
		else if (operation == "push") {
			// Check if a list of that name exists (in any of the 3 maps)
			if (
				imap.find(list_name) == imap.end() &&
				dmap.find(list_name) == dmap.end() &&
				smap.find(list_name) == smap.end()
			){
				output << "ERROR: This name does not exist!" << '\n';
			}

			// Lookup list in appropriate map and pop value
			else if (imap.find(list_name) != imap.end()) {
				imap[list_name]->push(std::stoi(value));
			}

			else if (dmap.find(list_name) != dmap.end()) {
				dmap[list_name]->push(std::stod(value));
			}

			else if (smap.find(list_name) != smap.end()) {
				smap[list_name]->push(value);
			}
		}

		// Processing "pop" command
		else if (operation == "pop") {
			// Check if a list of that name exists (in any of the 3 maps)
			if (
				imap.find(list_name) == imap.end() &&
				dmap.find(list_name) == dmap.end() &&
				smap.find(list_name) == smap.end()
			){
				output << "ERROR: This name does not exist!" << '\n';
			}

			else if (imap.find(list_name) != imap.end()) {
				if (imap[list_name]->get_size() == 0) {
					output << "ERROR: This list is empty!" << '\n';
				}
				else {
					output << "Value popped: " << imap[list_name]->pop() << '\n';
				}
			}

			else if (dmap.find(list_name) != dmap.end()) {
				if (dmap[list_name]->get_size() == 0) {
					output << "ERROR: This list is empty!" << '\n';
				}
				else {
					output << "Value popped: " << dmap[list_name]->pop() << '\n';
				}
			}

			else if (smap.find(list_name) != smap.end()) {
				if (smap[list_name]->get_size() == 0) {
					output << "ERROR: This list is empty!" << '\n';
				}
				else {
					output << "Value popped: " << smap[list_name]->pop() << '\n';
				}
			}
		}
	}
}
