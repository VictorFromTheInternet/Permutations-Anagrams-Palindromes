#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <string>
#include <algorithm>
#include <vector>
#include "HashTable.h"

using namespace std;

// global var
vector<string> dict;

// file input for hash table
void read_file(ifstream& infile){

	while(infile){
		string temp = "";
		getline(infile, temp);
		dict.push_back(temp);
		//cout << temp;
	}
}




int main() {
	// create an obj, insert some strings
	HashTable ht;

	// open file
	ifstream infile;
	infile.open("dictionary.txt");
		if(!infile){cout << "ERROR could not open infile" <<endl;}

	read_file(infile);
	
		for(int i=0; i<dict.size(); i++){
			ht.addItem(dict.at(i));
		}
	
		ht.printTable();
	

	// prompt user
	string input;
	cout << "Hello, Enter a one word string: ";
	cin >> input;

	// tests
		
	
}