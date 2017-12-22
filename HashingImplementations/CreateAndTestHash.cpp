#include "QuadraticProbing.h"
#include "LinearProbing.h"
#include "DoubleHashing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template <typename HashTableType>
void fillTable(HashTableType &hash_table, ifstream &dictionary){
  string line;
  while(getline(dictionary, line)){
    hash_table.Insert(line);
  }
  dictionary.close();
}

template <typename HashTableType>
void
TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
  cout << "TestFunctionForHashTables..." << endl;
  cout << "Words filename: " << words_filename << endl;
  cout << "Query filename: " << query_filename << endl;
  hash_table.MakeEmpty();

  ifstream dictionary;
  dictionary.open(words_filename);
  fillTable(hash_table, dictionary);

  size_t collisions = hash_table.GetCollisions();
  size_t numItems = hash_table.GetCurrentSize();
  size_t tableSize = hash_table.GetMaxSize();

  cout << "Collisions: " << collisions << endl;
  cout << "Number of items: " << numItems << endl;
  cout << "Size of hash table: " << tableSize << endl;
  cout << "Load factor: " << (float)numItems / (float)tableSize << endl;
  cout << "Avg. number of collisions: " << (float)collisions / (float)numItems << endl;
}

int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
    return 0;
  }

  const string words_filename(argv[1]);
  const string query_filename(argv[2]);
  const string param_flag(argv[3]);

  if (param_flag == "linear") {
    HashTableLinear<string> linear_probing_table;
    TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);
  } else if (param_flag == "quadratic") {
    HashTable<string> quadratic_probing_table;
    TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);
  } else if (param_flag == "double") {
    HashTableDouble<string> double_probing_table;
    TestFunctionForHashTable(double_probing_table, words_filename, query_filename);
  } else {
    cout << "Unknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
  }
  return 0;
}
