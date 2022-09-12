/*******************************************************
	File: hash.cpp

	Description: 
	
*******************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>

#include "HashTable.h"

using namespace std;


// default constructor
HashTable::HashTable()
{
	// initialize each index/pointer/empty node item
	for(int i=0; i < tableSize; i++)
	{
		// create and initialze the hash table (null linked list for each index)
		hashArray[i] = new item;	// index points at something now
		
		hashArray[i] -> word = "empty";
		hashArray[i] -> next = nullptr;				// initializes the new item
		
	}
}


// destructor
HashTable::~HashTable()
{
   item* current; 
   
   // transverses the hashArray
   for(int i=0;i<tableSize;i++)
   {
   	  // traverses through each linked list and deletes nodes
      while(hashArray[i] != NULL)
      {
      	// set current to the front of the linked list
      	current = hashArray[i];
      	
	        // set the next elem as the front of the linked list
	        hashArray[i] = hashArray[i] -> next;
        
        // delete the node that used to be the front
        delete current; 
         
      }
   }
}


// add items, point the root's link, or replace the info in root
void HashTable::addItem(string word)
{
	
	// run the name through the hash function to determine storage index
	int index = hashFunction(word);
	
	// if the list at the index is empty, store item there
	if(hashArray[index]-> word == "empty")
	{
		// if empty fill it in w input
		hashArray[index]->word = word;
	}
	
	// else the list at the index is NOT empty, so traverse and store at end of list
	else
	{
		// declare and initialize current pointer for traversal use 
		item* current = hashArray[index];
		
		// create and populate new node item that will be added
		item* n = new item;
		n->word = word;
		n->next = nullptr;		// since it will be added to the end initialize it to null
		
		// traverse through the list to find the end
		while(current->next != NULL)
		{
			current = current->next;
		}
		
		// add the new item to the end of the appropriate list
		current->next = n;
		
	}
	
}

//index size
int HashTable::indexSize(int index)
{
	
	// declare count and initialize to zero
	int count = 0;
	
	// check to see if there are no items in the list at the index
	if(hashArray[index]->word == "empty")
	{
		// return the count (which will be zero since it's empty)
		return count;
	}
	
	// else there are items in the list so traverse through and increment count
	else
	{
		// increment count (for the first item in the list)
		count++;
		
		// declare and initialize current pointer for traversal
		item* current = hashArray[index];
	
		// traverse throught the rest of the list
		while(current->next != NULL)
		{
			// increment count
			count++;
			// advance to the next node item
			current = current->next;
		}
	}
	
	// return the count (number of items in the list)
	return count;
	
}


// output index
void HashTable::printItemsInIndex(int index)
{
	item* current = hashArray[index]; // current points to index/list
	
	if(current->word == "empty")
	{
		cout << "INDEX = " << index << " is empty";
	}
	else
	{
		cout << "INDEX " << index <<  " contains the following items" << endl << endl;
		
		while(current != NULL)
		{
			
			cout << current->word << endl;
			cout << "------------" << endl;
			
			current = current->next;
		}
		
	}
	
}


// output table
void HashTable::printTable()
{
	int number;
	
	cout << "---------------------------------------------------------" << endl;
	cout << "                 FULL HASH TABLE CONTENTS" << endl;
	cout << "---------------------------------------------------------" << endl << endl;
	for(int i=0; i < tableSize; i++)
	{
		number = indexSize(i);
		cout << endl;
		cout << "Number of items in list location " << i << ": " << number << endl;
		cout << "---------------------------------------" << endl;
		
		// output all the items at current index
		printItemsInIndex(i);
		
		cout << endl;

	}	
	
}


// search table
void HashTable::searchTable(string word)
{
	// run the name through the hash function to determine which list
	// the person should be if they are in the hash table
	int index = hashFunction(word);
	
	
	// declare and initialize working variables
	bool foundItem = false;
	
	// create and initialize current pointer to the beginning of the correct list
	item* current = hashArray[index];
	
	// traverse through the list until the item is found or the end is reached
	while(current != nullptr && foundItem != true)
	{
		// if the person is found
		if(current->word == word)
			foundItem = true;
		
		// For testing...output all the names that get searched during the process
		cout << current->word << endl;
		
		// advance to the next person in the list
		current = current->next;
		
	}
	
	// after traversal, output phone number or message if not found
	if(foundItem == true)
		cout << "Word was found at index: " << index << endl;
		
	else
		cout << "Word: " << word << ", was not found in the hash table" << endl;
	
	
}

void HashTable::findAnagrams(string word){
	vector<string> anagramList;
	int index = hashFunction(word);

	// traverse list
	item* current = hashArray[index]; // current points to index/list
	
	if(current->word == "empty")
	{
		cout << "INDEX = " << index << " is empty";
	}
	else
	{
		
		while(current != NULL)
		{
			if( anagramTest(word, current->word)){
				anagramList.push_back(current->word);
			}
			
			current = current->next;
		}
		
	}

	for(int i =0; i < anagramList.size(); i++){
			cout << anagramList.at(i) << endl;
		}
}
bool HashTable::anagramTest(string one, string two){
	if(one.length() != two.length())
		cout << one<<" == "<<two << " : FALSE";
	
	else{
		sort(one.begin(), one.end());
		sort(two.begin(), two.end());

		if(one == two) {
			cout << one<<" == "<<two << " : TRUE";
			return;
		}
	}

	cout << one<<" == "<<two << " : FALSE";
}

// remove items
void HashTable::removeItem(string word)
{
	// run name through hash function to determine index of 
	// list where the person should be.
	int index = hashFunction(word);
	
	// declare pointers needed for deletion process
	item* deletePointer;
	item* current;
	item* trail;
	

	// Case 0 - bucket is empty
	if(hashArray[index]->word == "empty")
	{
		cout << word << " was not found in the Hash Table" << endl;
	}
	
	// Case 1 - only 1 item contained in bucket and that item has matching name
	else if(hashArray[index]->word == word && hashArray[index]->next == nullptr)
	{
		// leave the node item there but change its name and phone number to empty
		hashArray[index]->word = "empty";
		
		// output confirmation message
		cout << word << " was removed from the Hash Table" << endl;
	}
	
	
	// Case 2 - match is located in the first item in the bucket but there are more items in the bucket
	else if(hashArray[index]->word == word)
	{
		// set deletePointer to keep track of where the item to be deleted is
		deletePointer = hashArray[index];
				
		// update beginning of list to be the next node item
		hashArray[index] = hashArray[index]->next;	// point "hashArray" to the next guy, deletePointer still pointed at og
		
		// delete the item
		delete deletePointer;
		
		// output confirmation message
		cout << word << " was removed from the Hash Table" << endl;
	}
	
	
	// Case 3 - bucket contains items but first item is not a match (search through the rest of the list)
	else
	{
		// set up current and trail for list traversal
		current = hashArray[index]->next;	// init to the 2nd since 1st wasnt search item
		trail = hashArray[index];
		
		// continue to traverse the list as long as end is not reached and no match
		while(current != nullptr && current->word != word)
		{
			// advance the trail and current pointers
			trail = current;	// move the trail up to current
			current = current->next;	// move current up one
		}
		
		// Case 3.1 - no match found and end of list reached
		if(current == nullptr)
		{
			cout << word << " was NOT found in the Hash Table" << endl;
		}
		// Case 3.2 - match is found
		
		else		// (should also handle the case of the search item being the last in the list)
		{
			// set the delete pointer and update the link of the previous node
			deletePointer = current;	// assign val to delptr
			current = current->next;	// advance the current ptr
			trail->next = current;		// beidge the gap in the linked list
			
			// delete the item
			delete deletePointer;
			
			
			// output confirmation message
			cout << word << " was removed from the Hash Table" << endl;
		}
		
	}
	
}


// hash function
int HashTable::hashFunction(string key)
{
	
	int hashSum = 0;
	int hashIndex;
	
	// loop to add up all the ASCII values
	for(int i=0; i < key.length(); i++)	
	{
		hashSum = hashSum + int(key[i]);
	}
	
	// mod the sum by the array size and assign result to hashIndex
	hashIndex = hashSum % tableSize;
	
	// return the hashIndex
	return hashIndex;

}

