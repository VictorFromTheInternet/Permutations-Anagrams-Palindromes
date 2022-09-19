/*

	This program will use string input, and then output permutations, anagrams from a data file, and test if its a palindrome

	Notes: troubleshoot & test the anagram search feature 

				maybe try a hash sum function with the hash index 
				to be able to troubleshoot the issue with the searching

*/
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
vector<string> perm_list;
vector<string> anagrams;

// input data into vector
void read_file(ifstream& infile){

	while(infile){
		string temp = "";
		getline(infile, temp);
		dict.push_back(temp);
	}

}

void isPalindrome(string str){
	int left = 0;
	int right = str.length()-1;

	while(left < right){
		// false tests, (32 char diff in ASCII cases)
		if(str[left] != str[right]){ // same case
			if((int)(str[left]+32) != (int)str[right]	&&	// L , r
				 (int)str[left] 		 != (int)str[right]+32){ // l, R

				cout << "String: "<<str<<" is NOT a Palindrome"<<endl << endl;
				return;
			}
		} 	
		
		// inc dec
		//cout << "left: "<<left<<", Right: "<<right <<endl;
		left++;
		right--;
	}

	cout << "String: "<<str<<" IS a Palindrome"<<endl<<endl;
}

void permutations(string str, int l, int r){
	
  // Base case 
  if (l == r) {
		perm_list.push_back(str);
	}
	// Permute
  else  { 	
		//cout << str << endl;
    for (int i = l; i <= r; i++) { 
    	swap(str[l], str[i]); // swap indexes

      permutations(str, l+1, r); // recursion 
																 //(All branches for top levels done here)
  
      swap(str[l], str[i]); //backtrack (Next Letter)
		}	
		
  } 	
}

void anagram_test(string one, string two){
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

string to_uppercase(string input){
	string temp = input;
	for(int i=0; i<input.length(); i++)
		temp[i] = ((int)temp[i] >= 97)? (int)temp[i]-32: (int)temp[i];
	return temp;
}




int main() {
	// create an obj, insert some strings
	HashTable ht;

	// open file
	ifstream infile;
	ofstream outfile_table;
	ofstream outfile_perm;
	infile.open("dictionary.txt");
		if(!infile){cout << "ERROR could not open infile" <<endl;}
	outfile_table.open("table_output.txt");
	outfile_perm.open("permutations_output.txt");

	// read file and add items to table
	read_file(infile);
	
		for(int i=0; i<dict.size(); i++){
			ht.addItem(dict.at(i));
		}

		cout << "Printing table ..." << endl;
		ht.printTable(outfile_table);
		cout << "Done printing, check 'table_output.txt'" << endl << endl;
		
	

	// prompt user
	string input;
	cout << "Hello, Enter a one word string: ";
	cin >> input;
	input = to_uppercase(input);

	// palindrome
	isPalindrome(input);

	// permutations
	permutations(input, 0, input.size()-1);
	cout << "To see all possible Permutations of your input ("<<perm_list.size()<<"),\ncheck 'permutations_output.txt' "<<endl;
		for(int i =0; i < perm_list.size(); i++){
			outfile_perm << perm_list.at(i) << endl;
		}
		

	// anagram test
	ht.searchTable(input);
	ht.findAnagrams(input);
		
	
}