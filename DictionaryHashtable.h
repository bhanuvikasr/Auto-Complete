/* Author: Dion Chung & Bhanu Renukuntla
   Date: 10/24/16
   Assignment: PA2
   This is the declaration for DictionaryHashtable which utilzes unordered_set
   from the standard library.
*/

#ifndef DICTIONARY_HASHTABLE_H
#define DICTIONARY_HASHTABLE_H

#include <string>
#include <unordered_set>

/**
 *  The class for a dictionary ADT, implemented as a Hashtable
 * When you implement this class, you MUST use a Hashtable
 * in its implementation.  The C++ unordered_set implements
 * a Hashtable, so we strongly suggest you use that to store
 * the dictionary.
 */
class DictionaryHashtable
{
public:

  /* Create a new Dictionary that uses a Hashset back end */
  DictionaryHashtable();

  /* Insert a word into the dictionary. */
  bool insert(std::string word);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

  /* Destructor */
  ~DictionaryHashtable();

private:
	std::unordered_set<std::string> dict_h;
        std::pair<std::unordered_set<std::string>::const_iterator,bool> ret;

};

#endif // DICTIONARY_HASHTABLE_H
