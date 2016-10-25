/* Author: Dion Chung & Bhanu Renukuntla
   Date: 10/24/16
   Assignment: PA2
   This defines benchdict, a function that benchmarks three dictionary
	 implementations, BST, Hash Table, and Ternary Trie. The three are measured
	 by the time it takes to perform 100 unsuccessful 'finds'.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include <cstdlib>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#define LETTERS 26
using namespace std;
using std::istream;
using std::istringstream;

int main(int argc, char**argv){

	int num_iterations = atoi(argv[3]);
	int min_size = atoi(argv[1]);
	int step_size = atoi(argv[2]);
	std::vector<std::pair<int, long long>> results_bst;
	std::vector<std::pair<int, long long>> results_ht;
	std::vector<std::pair<int, long long>> results_dt;

	// get lines in file
	ifstream f;
	string line;
	int line_count;
	f.open(argv[4]);
	for (line_count = 0; getline(f, line); ++line_count);

	for (int i =0;i<num_iterations;i++){
		// reset the if stream
		ifstream in;
		Utils u;
		DictionaryBST d_bst;
		DictionaryHashtable d_ht;
		DictionaryTrie dt;

		in.open(argv[4]);

		int size = min_size +i*step_size;

		int insert_count = size;
		if (line_count<size) {
			cout << "WARNING: More words than in file" << endl;
			insert_count = line_count;
		}

		u.load_dict(d_bst, in, size);

		u.load_dict(d_ht, in, size);

		u.load_dict(dt, in, size);

		string junk;
		string data = "";
		string temp_word = "";
		string word = "";
		vector<string> word_string;
		vector<std::string> hundred_words;
		int j = 0;
		while(getline(in, data) && j < 100)
		{
			if(in.eof()) break;
			temp_word = "";
			word = "";
			data = data + " .";
			istringstream iss(data);
			iss >> junk;
			while(1)
			{
				iss >> temp_word;
			if(temp_word == ".") break;
			if(temp_word.length() > 0) word_string.push_back(temp_word);
			}
			for(int k = 0; k < word_string.size(); k++)
			{
				if(k > 0) word = word + " ";
				word = word + word_string[k];
			}

			hundred_words.push_back(word);
			word_string.clear();
			j++;
		}

		long long rv = 0;
		int iter = 50;
		for(int i=0; i<iter; i++){
			Timer t;
			t.begin_timer();
			for(int k=0; k < hundred_words.size(); k++) {
				d_bst.find(hundred_words[k]);
			}
			 rv += t.end_timer();
		}
		results_bst.push_back(std::make_pair(insert_count, rv/iter));
		long long rv2 =0;
		for(int i =0; i<iter;i++){
			Timer t2;
			t2.begin_timer();
			for(int k=0; k < hundred_words.size(); k++) {
				d_ht.find(hundred_words[k]);
			}

			rv2 += t2.end_timer();
		}
		results_ht.push_back(std::make_pair(insert_count, rv2/iter));

		long long rv3 =0;
		for(int i =0; i<iter;i++){
			Timer t3;
			t3.begin_timer();
			for(int k=0; k < hundred_words.size(); k++) {
				dt.find(hundred_words[k]);
			}
			rv3 += t3.end_timer();
		}
		results_dt.push_back(std::make_pair(insert_count, rv3/iter));
	}

	cout << "DictionaryBST" << endl;
	for (std::vector<std::pair<int, long long>>::iterator it = results_bst.begin() ; it != results_bst.end(); ++it){
		cout << it->first<< ' ' << it->second<< endl;
	}

	cout << "DictionaryHashtable" << endl;
	for (std::vector<std::pair<int, long long>>::iterator it = results_ht.begin() ; it != results_ht.end(); ++it){
		cout << it->first<< ' ' << it->second<< endl;
	}

	cout << "DictionaryTrie" << endl;
	for (std::vector<std::pair<int, long long>>::iterator it = results_dt.begin() ; it != results_dt.end(); ++it){
		cout << it->first<< ' ' << it->second<< endl;
	}
}
