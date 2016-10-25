/* Author: Dion Chung & Bhanu Renukuntla
   Date: 10/24/16
   Assignment: PA2
   This is the declaration for DictionaryBST which utilzes set from the
   standard library.
*/

#ifndef DICTIONARY_BST_H
#define DICTIONARY_BST_H

#include <string>
#include <set>

/**
 *  The class for a dictionary ADT, implemented as a BST
 * When you implement this class, you MUST use a balanced binary
 * search tree in its implementation.  The C++ set implements
 * a balanced BST, so we strongly suggest you use that to store
 * the dictionary.
 */
class DictionaryBST
{
public:

  /* Create a new Dictionary that uses a BST back end */
  DictionaryBST();

  /* Insert a word into the dictionary. */
  bool insert(std::string word);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

  /* Destructor */
  ~DictionaryBST();

private:
	std::set<std::string> dict_bst;
        std::pair<std::set<std::string>::iterator,bool> ret;
};

#endif // DICTIONARY_BST_H
