/*******************************************************
	File: hash.h
*******************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;


#ifndef HashTable_H
#define HashTable_H


class HashTable
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
		HashTable();
		~HashTable();
		int hashFunction(string key);		// will return int/index value (where to store)
		void addItem(string word);
		int indexSize(int index);
		
		// output functions 
		void printTable(ofstream& outfile);
		void printItemsInIndex(ofstream& outfile, int index);
	

		
		void searchTable(string word);	// will search the array index (which points to linked list)
		void findAnagrams(string word);
		bool anagramTest(string one, string two);
		void removeItem(string word);
		
};

#endif
