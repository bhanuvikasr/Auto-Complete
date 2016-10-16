#include "util.h"
#include "DictionaryTrie.h"
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
				if(i!=word.length()-1){ // checking if pointer is at the end of the string.
					bool end_of_word = (i==word.length()-2);
					curr->middle = new TSTNode(word[i+1],end_of_word,end_of_word?freq:0);
					curr = curr->middle;
					i++;
					if (end_of_word) return true;
					
				}
				// checking if isWord is false. If false change it to true to insert the word
				else if(!curr->isWord){ 
					curr->isWord = true;
					curr->freq = freq;
					return true;
				}
				else {
					// the word already exists since isWord is true. Update freq is greater.
					if (curr->freq<freq) curr->freq = freq;
					return false;
                                } 
			}
			else {	// have to repeat whole thing again.
			  if(i==word.length()-1){ // if end of the word
				if(!curr->isWord){ // checking if the bool value is set to false.
					curr->isWord = true;
					curr->freq = freq;
					return true;
				}
				else { // trying to reinsert.
                                        if (curr->freq<freq) curr->freq = freq;
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
		// word is less than data in the node, traverse left
		else if(word[i]<curr->data) {
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
	if(word.length()==0){
		return false;
	}
	TSTNode* curr = root;
	for(unsigned int i=0; i<word.length();){
		int f =0;
		bool isWord = false;
		if(curr != NULL) {
			if(curr->data == word[i]){
				i++;
				f = curr->freq;
				isWord = curr->isWord;
				curr=curr->middle;
			}
			else if (word[i] < curr->data){
				curr = curr->left;
			}
			else {
				curr = curr ->right;
			}
		}
		else return false;
		if(i==word.length()&&isWord){
			cout<<"freq is " << f<<"... ";
			return true;
		}
	}
	
	return false;
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
  return words;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){}
