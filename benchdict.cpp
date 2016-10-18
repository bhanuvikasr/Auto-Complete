#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include<algorithm>
#include<set>
#include<cstdlib>
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
	int step_size =atoi(argv[2]);
	std::vector<std::pair<int, long long>> results_bst;
	std::vector<std::pair<int, long long>> results_ht;
	std::vector<std::pair<int, long long>> results_dt;
	
	for (int count=0; count < argc; ++count)
        std::cout << count << " " << argv[count] << '\n';
	
	//
	//cout << num_iterations << min_size << step_size;
	
	for (int i =0;i<num_iterations;i++){
		cout << i << " Num of it " << num_iterations << endl;
		// reset the if stream
		ifstream in;
		Utils u;
		DictionaryBST d_bst;
		DictionaryHashtable d_ht;
		DictionaryTrie dt;
		
		in.open(argv[4]);
		
		int size = min_size +i*step_size;
		//cout << size;
		
		u.load_dict(d_bst, in,size);
		
		u.load_dict(d_ht, in,size);
		
		u.load_dict(dt, in,size);
		
		string junk;
		string data = "";
		string temp_word = "";
		string word = "";
		vector<string> word_string; 
		//unsigned int i = 0;
		//bool tt;
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
		
		cout << hundred_words.size() << endl ;
		long long rv =0;
		int iter = 50000;
		for(int i =0; i<iter;i++){
			Timer t;
			t.begin_timer();
			for(int k=0; k < hundred_words.size(); k++) {
				d_bst.find(hundred_words[k]);
			}
			//cout << "This is k " << k << endl;
			 rv += t.end_timer();
		}
		results_bst.push_back(std::make_pair(size, rv/iter));
		long long rv2 =0;
		for(int i =0; i<iter;i++){
			Timer t2;
			t2.begin_timer();
			for(int k=0; k < hundred_words.size(); k++) {
				d_ht.find(hundred_words[k]);
			}
			
			rv2 += t2.end_timer();
		}
		results_ht.push_back(std::make_pair(size, rv2/iter));		

		long long rv3 =0;
		for(int i =0; i<iter;i++){
			Timer t3;
			t3.begin_timer();
			for(int k=0; k < hundred_words.size(); k++) {
				dt.find(hundred_words[k]);
			}
			rv3 += t3.end_timer();
		}
		results_dt.push_back(std::make_pair(size, rv3/iter));	
			
	
	
	}

cout << "DictionaryBST" << endl;
		//cout << results_bst.size();
		for (std::vector<std::pair<int, long long>>::iterator it = results_bst.begin() ; it != results_bst.end(); ++it){
			std::cout << it->first<< ' ' << it->second<< endl;
		}
		
		cout << "DictionaryHashtable" << endl;
		for (std::vector<std::pair<int, long long>>::iterator it = results_ht.begin() ; it != results_ht.end(); ++it){
			std::cout << it->first<< ' ' << it->second<< endl;
		}
		
		cout << "DictionaryTrie" << endl;	
		
		for (std::vector<std::pair<int, long long>>::iterator it = results_dt.begin() ; it != results_dt.end(); ++it){
			std::cout << it->first<< ' ' << it->second<< endl;
		}
}