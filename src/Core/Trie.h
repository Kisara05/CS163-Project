#ifndef TRIE_H
#define TRIE_H
#include "Data.h"
#include <string>
#include <unordered_map>
#include <vector>
#define TRIE_TEMPLATE template <typename T>

TRIE_TEMPLATE
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
    Node(T *data, bool isEnd = false);
    ~Node();

    std::unordered_map<char, Node *> children;
    T *data;
    bool isEnd;
  };

public:
  Trie();
  ~Trie();

  Result insert(T *data);
  Result insert(std::string word);
  Result remove(std::string word);
  Result contains(std::string word);
  T *find(std::string word);
  void clear();
  std::vector<T *> startsWith(std::string prefix);

private:
  Result insert(std::string word, T *data);

private:
  Node *root;
};

#endif // TRIE_H

#include "Trie.cpp"
