/* Author: Dion Chung & Bhanu Renukuntla
   Date: 10/24/16
   Assignment: PA2
   This defines benchhash, a function that benchmarks two hashing functions,
   measuring the number of collisions and the average number of steps to search
   for a key.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include <cstdlib>
#include <vector>
#include <array>
#include <cmath>
#define LETTERS 26
using namespace std;
using std::istream;
using std::istringstream;

/*
Hash function based on folding, characters in string are broken into chunks of
4 and each character's ASCII code value is summed up, modified by a multiple of
256.
http://research.cs.vt.edu/AVresearch/hashing/strings.php
*/
long sfold(string s, unsigned int m_size) {
  int intLength = s.length() / 4;
  long sum = 0;
  for (int j = 0; j < intLength; j++) {
    string subs = s.substr(j * 4, (j * 4) + 4);
    long mult = 1;
    for (int k = 0; k < subs.length(); k++) {
      sum += subs[k] * mult;
      mult *= 256;
    }
  }

  string subs = s.substr(intLength * 4);
  long mult = 1;
  for (int k = 0; k < subs.length(); k++) {
    sum += subs[k] * mult;
    mult *= 256;
  }

  return(abs(sum) % m_size);
}

/*
djb2 hash function, geometric series that multiplies the rolling hash value with
33 and then adds the current character's ASCII code value. Begins with 5381.
http://www.cse.yorku.ca/~oz/hash.html
*/
long djb2_hash(string s, unsigned int m_size) {
  unsigned long hash = 5381;

  for (int k = 0; k < s.length(); k++) {
      hash = ((hash << 5) + hash) + (int)s[k]; /* hash * 33 + c */
  }

  return hash % m_size;
}

int main(int argc, char**argv){
  string dictfile = argv[1];
  unsigned int num_words = atoi(argv[2]);
  unsigned int m_size = 2 * num_words;
  vector<set<string>> hashtable1;
  hashtable1.resize(m_size);
  vector<int> results_ht1;
  float total_steps1 = 0;
  int worst_set1 = 0;
  vector<set<string>> hashtable2;
  hashtable2.resize(m_size);
  vector<int> results_ht2;
  float total_steps2 = 0;
  int worst_set2 = 0;

  ifstream in;
  in.open(dictfile);
  string junk;
  string data = "";
  string temp_word = "";
  string word = "";
  vector<string> word_string;
  int j = 0;
  while(getline(in, data) && j < num_words)
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

    hashtable1[sfold(word, m_size)].insert(word);
    hashtable2[djb2_hash(word, m_size)].insert(word);
    word_string.clear();
    j++;
  }

  // calculate statistics for hash function 1
  for (int k=0; k<hashtable1.size(); k++) {
    if (results_ht1.size()<=hashtable1[k].size()) {
      worst_set1 = hashtable1[k].size();
      results_ht1.resize(hashtable1[k].size()+1);
    }
    int steps = 0;
    for (int j=0; j<hashtable1[k].size()+1; j++) steps += j;
    total_steps1 += steps;
    results_ht1[hashtable1[k].size()]++;
  }

  // print statistics for hash function 1
  cout << "Printing the statistics for Fold Hash Function with hash table size "
    << m_size << endl;
  cout << "#hits\t#slots receiving the #hits" << endl;
  for (int j=0; j<results_ht1.size(); j++) {
    cout << j << "\t" << results_ht1[j] << endl;
  }
  cout << "The average number of steps for a successful search for hash function1 would be "
    << total_steps1/num_words << endl;
  cout << "The worst case steps that would be needed to find a word is "
  << worst_set1 << endl;

  // calculate statistics for hash function 2
  for (int k=0; k<hashtable2.size(); k++) {
    if (results_ht2.size()<=hashtable2[k].size()) {
      worst_set2 = hashtable2[k].size();
      results_ht2.resize(hashtable2[k].size()+1);
    }
    int steps = 0;
    for (int j=0; j<hashtable2[k].size()+1; j++) steps += j;
    total_steps2 += steps;
    results_ht2[hashtable2[k].size()]++;
  }

  // print statistics for hash function 2
  cout << "Printing the statistics for djb Hash Function with hash table size "
    << m_size << endl;
  cout << "#hits\t#slots receiving the #hits" << endl;
  for (int j=0; j<results_ht2.size(); j++) {
    cout << j << "\t" << results_ht2[j] << endl;
  }
  cout << "The average number of steps for a successful search for hash function2 would be "
    << total_steps2/num_words << endl;
  cout << "The worst case steps that would be needed to find a word is "
    << worst_set2 << endl;

}
