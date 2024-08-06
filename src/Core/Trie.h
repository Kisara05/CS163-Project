#ifndef TRIE_H
#define TRIE_H
#include "Data.h"
#include <string>
#include <unordered_map>
#include <vector>

class Trie {
public:
  enum class Result {
    SUCCESS = 20,
    NOT_FOUND,
    ALREADY_EXISTS,
    FAILED,
    EMPTY_STRING
  };

private:
  struct Node {
    Node();
    Node(Data *data, bool isEnd = false);
    ~Node();

    std::unordered_map<char, Node *> children;
    Data *data;
    bool isEnd;
  };

public:
  Trie();
  ~Trie();

  Result insert(Data *data);
  Result insert(std::string word);
  Result remove(std::string word);
  Result contains(std::string word);
  Data *find(std::string word);
  void clear();
  std::vector<Data *> startsWith(std::string prefix);

private:
  Result insert(std::string word, Data *data);

private:
  Node *root;
};

#endif // TRIE_H
