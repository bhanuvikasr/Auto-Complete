/* Author: Dion Chung & Bhanu Renukuntla
   Date: 10/24/16
   Assignment: PA2
   This is the definition for TSTNode and DictionaryTrie. Lower case letters and
	 space are valid characters, while capital letters are considered invalid, due
	 to properties of Ternary Trie, it is accepted.
*/

#include "util.h"
#include "DictionaryTrie.h"
#include <list>
using namespace std;


TSTNode::TSTNode(const char d, bool w, const unsigned int f) : data(d), isWord(w),
	freq(f), left(0), middle(0), right(0), parent(0) {}


/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie():root(0) {}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
 	bool DictionaryTrie::insert(std::string word, unsigned int freq){
	if(word.length()==0){
		return false;
	}
	if (root==NULL) {
		if (word.length()==1) {
			root = new TSTNode(word[0], true, freq);
		}
		else {
			root = new TSTNode(word[0], false, 0);
		}
	}
	TSTNode* curr = root;
	for (unsigned int i=0; i<word.length();) { // iterates over i and also over nodes of the tree
		if (curr->data==word[i]) {
			if (curr->middle==NULL ) { // create new node or end searching.
				if(i!=word.length()-1){ // checking if the pointer is at the end of the string.
					bool end_of_word = (i==word.length()-2);
					curr->middle = new TSTNode(word[i+1],end_of_word,end_of_word?freq:0);
					curr = curr->middle;
					i++;
					if (end_of_word) return true;

				}
				else if(!curr->isWord){ // checking if the bool value is set to false. If yes change it to true to insert the word
					curr->isWord = true;
					curr->freq = freq;
					return true;
				}
				else return false; // the word already exists since isWord is true.
			}
			else {	// have to repeat whole thing again.
			  if(i==word.length()-1){ // if end of the word
				if(!curr->isWord){ // checking if the bool value is set to false.
					curr->isWord = true;
					curr->freq = freq;
					return true;
				}
				else { // trying to reinsert.
					return false;
				}
			  }
			  else{
				curr = curr->middle;
				i++;
				continue;
			  }
			}
		}
		else if(word[i]<curr->data) { // word is less than data in the node, traverse left
			if(curr->left==NULL){
				bool end_of_word = (i==word.length()-1);
				curr->left = new TSTNode(word[i], end_of_word,end_of_word?freq:0);
				curr = curr->left;
				if (end_of_word) return true;

			}
			else{ // there is node at left position
				curr = curr->left;
				continue;
			}
		}
		else{ // traverse right
			if(curr->right==NULL){
				bool end_of_word = (i==word.length()-1);
				curr->right = new TSTNode(word[i], end_of_word,end_of_word?freq:0);
				curr = curr->right;
				if (end_of_word) return true;

			}
			else{ // there is node at right position
				curr = curr->right;
				continue;
			}
		}
	}
	return false;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
	TSTNode* node;
	node = getPrefixNode(word);
	if(node==NULL){
		return false;
	}
	else{
		return node->isWord;
	}

	return false;
}

/* getPrefixNode is a helper function that returns the pointer to the last
letter of the word. If the word is not found in the Dict then it returns a
NULL pointer.
  */
TSTNode* DictionaryTrie::getPrefixNode(std::string word) const{
	if(word.length()==0){
		return NULL;
	}
	TSTNode* curr = root;
	for(unsigned int i=0; i<word.length();){
		int f = 0;
		if(curr != NULL) {
			if(curr->data == word[i]){
				i++;
				if(i==word.length()){
					return curr;
				}
				f = curr->freq;
				curr = curr->middle;
			}
			else if (word[i] < curr->data){
				curr = curr->left;
			}
			else {
				curr = curr->right;
			}
		}
		else return NULL;
		if(i==word.length()){
			cout << "freq is " << f << "... ";
			return curr;
		}
	}
	return NULL;
}

/* Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
  std::vector<std::string> words;
  std::list<std::pair<std::string ,unsigned int>> top_words;
  TSTNode* node;
  if(num_completions==0 || prefix==""){
		cout << "WARNING, this empty search will return 0 results" << endl;
	  return words;
  }
  // get the node of the prefix
  node = getPrefixNode(prefix);
  if(node!=NULL){
		if(node->isWord){
		  top_words.push_back(std::make_pair(prefix, node->freq));
		}
  }
  else {
	  return words;
  }
  getWords(node->middle,prefix,top_words, num_completions);

  // order and copy the words to words vector

  while(top_words.size()!=0){
	  unsigned int f_max = 0;
	  std::list<std::pair<std::string ,unsigned int>>::iterator it_max;
	  for (std::list<std::pair<std::string ,unsigned int>>::iterator it=top_words.begin(); it != top_words.end(); ++it){
		  if(it->second > f_max){
			  f_max = it->second;
				it_max = it;
			}
		}

		words.push_back(it_max->first);
		top_words.erase(it_max);
  }

  return words;
}

void DictionaryTrie::getWords(TSTNode* node, std::string str, std::list<std::pair<std::string ,unsigned int>> & top_words, unsigned int num_completions) const{
	if(node==NULL){return;}
	else{
		std::string temp_str = str + node->data;
		if (node->isWord){ // if the node is a word update the top_words list
			// add the pair if its freq is higher than min freq in the list.
			if (top_words.size()<num_completions){
				top_words.push_back(std::make_pair(temp_str, node->freq));
			}
			else {
				unsigned int f_new = node->freq;
				unsigned int f_min = 0;
				std::list<std::pair<std::string, unsigned int>>::iterator it_min;
				for (std::list<std::pair<std::string, unsigned int>>::iterator it=top_words.begin(); it != top_words.end(); ++it){
					if(it->second < f_min){
						f_min = it->second;
						it_min = it;
					}
				}

				if (f_min < f_new){
					top_words.erase(it_min);
					top_words.push_back(std::make_pair(temp_str,f_new));
				}
			}
		}
		getWords(node->middle, temp_str, top_words, num_completions);
		getWords(node->left, str, top_words, num_completions);
		getWords(node->right, str, top_words, num_completions);
	}
	return;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){
	deleteAll(root);
	
}

void DictionaryTrie::deleteAll(TSTNode* n) const
{
  // TODO
  // post order traversal of nodes
  if(!n){ // exits if its a null pointer
	  return;
  }
  else{
	deleteAll(n->left);
	deleteAll(n->middle);
	deleteAll(n->right);
	delete n;
	return;
	
  }
}
