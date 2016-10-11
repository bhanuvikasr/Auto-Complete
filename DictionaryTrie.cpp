#include "util.h"
#include "DictionaryTrie.h"


TSTNode::TSTNode(const char & d, bool w, const int & f) : data(d), isWord(w), 
	freq(f), left(0), middle(0), right(0), parent(0) {}


/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
	if(word.len==0){
		return false;
	}
	if (root==NULL) {
		if (word.len==1) {
			root = new TSTNode(word[0], true, freq);
		}
		else {
			root = new TSTNode(word[0], false, 0);
		}
	}
	TSTNode* curr = root;
	for (int i=0; i<word.len; i++) {
		if (curr->data==word[i]) {
			if (curr->middle==NULL ) {
				if(i!=word.len-1){
					//bool end_of_word = (i==word.len-2)
					curr->middle = new TSTNode(word[i+1],false,0);
					curr = curr->middle;
				}
				else return false; // the word already exists
			}
			else {	// going to left or right
			  curr = curr->middle;
			  if(word[i]<curr->data){// going to left node
				  if (curr->left==NULL ) {
				    if(i!=word.len-1){
					//bool end_of_word = (i==word.len-2)
					curr->left = new TSTNode(word[i+1],false,0);
					curr = curr->left;
				    }
				    else return false; // word already exista
				  }
				  else return false; // word cannot be inserted because there is already something at this place.
				 }
				else{// going to right node
				  if (curr->right==NULL ) {
				    if(i!=word.len-1){
					//bool end_of_word = (i==word.len-2)
					curr->right = new TSTNode(word[i+1],false,0);
					curr = curr->right;
				    }
				    else return false; // word already exists
				  }
				  else return false; // word cannot be inserted because there is already something at this place.
				 }
				}
			}
			
			 
		}
	else {
	  while (word[i]!=curr->data) {
	    if 
	}
		else if (word[i]<curr->data) {
			curr = curr->l
		else {

		}
			if (curr==NULL) {
				TSTNode* created(
	
  return false;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
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
