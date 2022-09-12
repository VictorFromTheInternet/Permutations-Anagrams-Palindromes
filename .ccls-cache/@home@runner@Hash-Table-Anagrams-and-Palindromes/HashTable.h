/*******************************************************
	File: hash.h
*******************************************************/

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;


#ifndef HASH_H
#define HASH_H


class hashTable
{
	private:
		
		static const int tableSize = 1000;
	
		// define a struct for each new node or item to be stored
		struct item
		{
			string word;
			item* next;
		};
		
		// array of pointers ( these will eventually point to other items -> in a linked lists)
		item* hashArray[tableSize];
	
	public:
		hashTable();
		~hashTable();
		int hashFunction(string key);		// will return int/index value (where to store)
		void addItem(string word);
		int indexSize(int index);
		
		// output functions 
		void printTable();
		void printItemsInIndex(int index);
		
		// output functions for output file
		void printTable(ofstream&);
		void printTableSummary(ofstream&);
		void printItemsInIndex(int index, ofstream&);
		
		void searchIndex(string item);	// will search the array index (which points to linked list)
		void removeItem(string item);
		
};

#endif
