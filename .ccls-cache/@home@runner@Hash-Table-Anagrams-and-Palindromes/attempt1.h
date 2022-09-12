/*

	This is the header & implementation for the hash table class
	This ht will implement chaining to prevent collisions

*/
#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include "OrderedLinkedList.h"

using namespace std;

//
//	Class Declaration
//
class HashTable{
	private:
		static const int num_hash_groups = 1000;
		list<string> table[num_hash_groups];
			// list0, index0 ... list1, index1

	public: 
		bool isTableEmpty() const;
		bool isIndexEmpty(int index) const;

		void insert(string item);
		void remove(string search_item);

		int hashValue(string item);
		void searchList(string search_item);
		void searchTable(string search_item);

		void output_at(int index);
		void output_table();
};


//
// Function defintions
//
bool HashTable::isTableEmpty() const{
	int sum=0;

	//step through table indexes, sum sizes
	for(int i=0; i<num_hash_groups; i++){
		sum += table[i].size();
	}

	return (sum == 0) ? true : false;
}
bool HashTable::isIndexEmpty( int index) const{
	if(index > 0 && index < num_hash_groups)
		return (table[index].size() == 0) ? true : false;
	else{
		cout << "enter a value between 0 and "<<num_hash_groups<<endl;
		return false;
	}
}

void HashTable::insert(string item){
	int key = hashValue(item);
	table[key].push_back(item);
}
//unfinished
void HashTable::remove( string search_item){
	// use iterator to search the list of strings
	int key = hashValue(search_item);
	for(auto& elm : table[key]){
		// remove element
	}
	
}

int HashTable::hashValue(string item){
	int ASCII_val = 0;
	for(int i =0; i< item.length(); i++){
		ASCII_val += (int)item[i];
	}
}

void HashTable::output_at(int index){
	if(table[index].size() < 1)
		cout << "Index Empty" << endl;
	else{
		for(auto& elm : table[index])
		cout << elm <<", ";
	}

}
/*
void HashTable::output_table(){
	for(int i=0; i < num_hash_groups; i++){
		this -> output_at(i);
	}
}
*/
