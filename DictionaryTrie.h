/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 */

#ifndef DICTIONARY_TRIE_H
#define DICTIONARY_TRIE_H

#include <vector>
#include <string>
#include <list>

/** 
 * Class that stores the characters, if the character is the terminus of a
 * word, as well as the frequency. It is contained by the TST.
 */
class TSTNode {

public:
  TSTNode* left;
  TSTNode* middle;
  TSTNode* right;
  TSTNode* parent;
  const char data;
  bool isWord;
  int freq; 

  TSTNode(const char d, bool w, const unsigned int f);

};


/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class DictionaryTrie
{
public:

  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

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
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);

  /* Destructor */
  ~DictionaryTrie();

private:
	TSTNode* root;
  // Add your own data members and methods here
  
  /**getPrefixNode is a helper function that returns the pointer to the last letter of the word. If the word is not found in the Dict then it returns a NULL pointer.
  */
  TSTNode* getPrefixNode(std::string word) const;
  
  void getWords(TSTNode* node, std::string str, std::list<std::pair<std::string ,unsigned int>> & top_words, unsigned int num_completions) const;
};

#endif // DICTIONARY_TRIE_H
