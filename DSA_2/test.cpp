#include "hash.h"
#include <iostream>
#include <string>



int main()
{   
	std::cout << "... test ..." << std::endl;
	hashTable table = hashTable();
	std::string dict[] = {"one", "two", "three", "four", "five"};
	for (std::string s : dict) { table.insert(s); }
	
    int x = 5;
    int *px;
    px = &x;
    
    table.setPointer("five", px);
    table.remove("two");
    
    int *py;
    
    for (auto i : dict) {
        std::cout << "\n" << i << std::endl;
        
        if (table.getPointer(i) != nullptr) {
            py = (int *)(table.getPointer(i));
            std::cout << "Pointer -> " << *py << std::endl;
        }
    }
    
	table.test();
}