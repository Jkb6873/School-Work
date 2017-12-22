#include "QuadraticProbing.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <ctype.h>

using namespace std;


//Fills hash table
template <typename HashTableType>
void FillTable(HashTableType &hash_table, ifstream &dictionary){
  string line;
  while(getline(dictionary, line)){
    hash_table.Insert(line);
  }
  dictionary.close();
}

//adds each character to the front, back or middle of the word
//if the resulting word is found, it is output and the amount found is incremented
template <typename HashTableType>
size_t AddChar(HashTableType &hash_table, string & word, ostream &output){
  size_t foundAmmount = 0;
  string permutation;
  for(size_t i = 0; i <= word.length(); ++i){
    for(int a=97; a<=122; a++){
      permutation = word.substr(0,i) + char(a) + word.substr(i);
      if(hash_table.Contains(permutation)){
        ++foundAmmount;
        output << permutation << endl;
      }
    }
  }
  return foundAmmount;
}

//Removes a character in each possible position
//If the resulting word is found, it is output and the amount found is incremented
template <typename HashTableType>
size_t RemChar(HashTableType &hash_table, string & word, ostream &output){
  size_t foundAmmount = 0;
  string permutation;
  for(size_t i=0; i<word.length(); i++){
    permutation = word;
    permutation.erase(i,1);
    if(hash_table.Contains(permutation)){
      ++foundAmmount;
      output << permutation << endl;
    }
  }
  return foundAmmount;
}

//Swaps each pair of letters in the supplied word
//If the resulting word is found, it is output and the amount found is incremented
template <typename HashTableType>
size_t SwapChar(HashTableType &hash_table, string & word, ostream &output){
  size_t foundAmmount = 0;
  string permutation;
  for(size_t i=0; i<word.length()-1; i++){
    permutation = word;
    swap(permutation[i], permutation[i+1]);
    if(hash_table.Contains(permutation)){
      ++foundAmmount;
      output << permutation << endl;
    }
  }
  return foundAmmount;
}

template <typename HashTableType>
void Spellcheck(HashTableType &table, ifstream &inStream, ostream &outFile)  {
  string word, line;
  int lineCounter = 0;
  while(getline(inStream, line)){
    ++lineCounter;
    std::stringstream lineToWord(line);
    while(getline(lineToWord, word, ' ')){
      if(word == "") continue;
      for(size_t i = 0; i < word.length(); ++i){
       	if(!isalnum(word[i]))
          word.erase(i, 1);
        word[i] = tolower(word[i]);
      }
      if(!table.Contains(word)){
        outFile << word << " (in line " << lineCounter << ")"
                << endl << "Possible Replacements:" << endl;
        size_t x = AddChar(table, word, outFile) +
                   RemChar(table, word, outFile) +
                   SwapChar(table, word, outFile);
        if (x == 0){outFile << "NO REPLACEMENTS FOUND" << endl;}
        outFile << endl;
      }
    }
  }

  inStream.close();
}
void TestOpen(const string &fileName, ifstream &streamName){
    try{
        streamName.open(fileName);
        if (!streamName.is_open())
            throw 1;
    } catch (int x){outFile
        std:: cout  << fileName
                    << " could not be opened." << endl
                    << "Try a different file" << endl;
        exit(1);
    }
}

int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <documentfile> <dictionaryfile>" << endl;
    return 0;
  }
  ifstream dictionary, document;
  TestOpen(argv[1], document);
  TestOpen(argv[2], dictionary);
  HashTable<string> doubleProbingTable;
  FillTable(doubleProbingTable, dictionary);
  Spellcheck(doubleProbingTable, document, cout);
  return 0;
}
