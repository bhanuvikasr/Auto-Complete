#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<set>
#include<cstdlib>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#define LETTERS 26
using namespace std;


int main(int argc, char** argv)
{

  //Initialize words
  vector<std::string> words;
  vector<string>::iterator wit;
  vector<string>::iterator wen;
  //initialize nonwords
  set<string> nope;
  set<string>::iterator nit;
  set<string>::iterator nen;

  //Initialize data structures
  DictionaryBST d_bst;
  DictionaryHashtable d_ht;
  DictionaryTrie dt;
  int t_bst, t_ht, tt;

  words.push_back(" harry");
  //words.push_back("hArry");
  //words.push_back("Harry");
  words.push_back("sriram");
  words.push_back("cse");
  words.push_back("crucio");
  words.push_back("autocomplete");
  
  words.push_back("har");
  words.push_back("auto");
  //words.push_back("hcse");
  //words.push_back("cs");
  //words.push_back("cscrucio");
  words.push_back("back");
  words.push_back("bat");
  //words.push_back("Auto");
  //words.push_back("H arry");
  words.push_back("  ");
  cout << "Inserting into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 2);
      //cout << t_bst << " " << t_ht << " "<< tt << "... ";
      if(!t_bst)
	{
	  cout << "failed for DictionaryBST... ";
	}
      if(!t_ht)
	{
	  cout << "failed for DictionaryHashset... ";
	}
      if(!tt)
	{
	  cout << "failed for DictionaryTrie... ";
	}
      if(t_bst && t_ht && tt)
	{
	  cout << "PASSED! :D ";
	}
      cout << endl;
    }

  cout << endl << "Re-inserting elements that were just inserted into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit,0);
      if(t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(!t_bst && !t_ht && !tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }

  cout << endl;

  
/*You are supposed to add more test cases in this file */
	
	cout << "finding words in Dictionaries..." << endl;
  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Finding: \"" << *wit << "\"... ";
      t_bst = d_bst.find(*wit);
      t_ht = d_ht.find(*wit);
      tt = dt.find(*wit);
      //cout << t_bst << " " << t_ht << " "<< tt << "... ";
      if(!t_bst)
	{
	  cout << "failed for DictionaryBST... ";
	}
      if(!t_ht)
	{
	  cout << "failed for DictionaryHashset... ";
	}
      if(!tt)
	{
	  cout << "failed for DictionaryTrie... ";
	}
      if(t_bst && t_ht && tt)
	{
	  cout << "PASSED! :D ";
	}
      cout << endl;
    }

	cout << endl << "Finding words that are not inserted in Dictionaries..." << endl;
	
	vector<std::string> find_words;
	find_words.push_back("hcse");
	find_words.push_back("csrucio");
	find_words.push_back("cs");
	find_words.push_back("ba");
	find_words.push_back("apple");
	find_words.push_back("bac");
	find_words.push_back(" ");
	
	
  wit = find_words.begin();
  wen = find_words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Finding: \"" << *wit << "\"... ";
      t_bst = d_bst.find(*wit);
      t_ht = d_ht.find(*wit);
      tt = dt.find(*wit);
      if(t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(!t_bst && !t_ht && !tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }

  cout << endl;

  // test fequency
  tt = dt.insert("frequency" , 1);
  if (!tt) cout << "Falied insert of 'frequency'" << endl;
  dt.find("frequency");
  tt = dt.insert("frequency" , 10);
  if (tt) cout << "Falied second insert of 'frequency'" << endl;
  dt.find("frequency");
  tt = dt.insert("frequency" , 100);
  if (tt) cout << "Falied third insert of 'frequency'" << endl;
  dt.find("frequency");

  ifstream in;
  in.open(argv[1]);
 
  Utils u;
  u.load_dict(dt, in);
  
  dt.find("zymoses");
  
  std::vector<std::string> predicted_words;
  predicted_words = dt.predictCompletions("zymo",14);
  
  std::cout << predicted_words.size();
  
  for (std::vector<std::string>::iterator it = predicted_words.begin() ; it != predicted_words.end(); ++it)
    std::cout << ' ' << *it;
  
  //cout<< predicted_words[0];
  return 0;
}
