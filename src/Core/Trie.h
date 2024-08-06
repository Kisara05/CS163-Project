#ifndef TRIE_H
#define TRIE_H
#include <string>
#include <unordered_map>

class Trie {
public:
  enum class Result { SUCCESS, NOT_FOUND, ALREADY_EXISTS };

private:
  struct Node {
    std::unordered_map<char, Node *> children;
    bool isEnd;
    Node();
    Node(bool isEnd);
    ~Node();
  };

public:
  Trie();
  ~Trie();

  Result insert(std::string word);
  Result remove(std::string word);
  Result search(std::string word);
  // bool startsWith(std::string prefix);

private:
  Node *root;
};

#endif // TRIE_H
