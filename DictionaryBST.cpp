/* Author: Dion Chung & Bhanu Renukuntla
   Date: 10/24/16
   Assignment: PA2
   This is the definition for DictionaryBST which utilzes set from the
	 standard library for functions find and insert.
*/

#include <set>
#include "util.h"
#include "DictionaryBST.h"

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word)
{
	ret = dict_bst.insert(word);
	return ret.second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const
{
	std::set<std::string>::iterator it;
	it=dict_bst.find(word);
	if (it!=dict_bst.end()) return true;
	return false;
}

/* Destructor */
DictionaryBST::~DictionaryBST(){}
