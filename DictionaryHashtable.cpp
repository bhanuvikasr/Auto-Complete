/* Author: Dion Chung & Bhanu Renukuntla
   Date: 10/24/16
   Assignment: PA2
   This is the definition for DictionaryHashtable which utilzes unordered_set
   from the standard library for functions find and insert.
*/

#include "util.h"
#include "DictionaryHashtable.h"
#include <unordered_set>


/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word)
{
	ret = dict_h.insert(word);
	return ret.second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const
{
        std::unordered_set<std::string>::const_iterator it;
	it = dict_h.find(word);
	if (it!=dict_h.end()) return true;
	return false;
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){}
