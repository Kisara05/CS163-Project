#include "Trie.h"

Trie::Node::Node() : isEnd(false) {}
Trie::Node::Node(bool isEnd) : isEnd(isEnd) {}
Trie::Node::~Node() {
  for (auto &child : children) {
    delete child.second;
  }
}
Trie::Trie() : root(new Node()) {}
Trie::~Trie() { delete root; }

Trie::Result Trie::insert(std::string word) {
  Node *current = root;
  for (char c : word) {
    if (current->children.count(c) == 0) {
      current->children[c] = new Node();
    }
    current = current->children[c];
  }
  if (current->isEnd) {
    return Trie::Result::ALREADY_EXISTS;
  }
  current->isEnd = true;
  return Trie::Result::SUCCESS;
}

Trie::Result Trie::remove(std::string word) {
  Node *current = root;
  for (char c : word) {
    if (current->children.count(c) == 0) {
      return Trie::Result::NOT_FOUND;
    }
    current = current->children[c];
  }
  if (!current->isEnd) {
    return Trie::Result::NOT_FOUND;
  }
  current->isEnd = false;
  return Trie::Result::SUCCESS;
}

Trie::Result Trie::search(std::string word) {
  Node *current = root;
  for (char c : word) {
    if (current->children.count(c) == 0) {
      return Trie::Result::NOT_FOUND;
    }
    current = current->children[c];
  }
  return current->isEnd ? Trie::Result::SUCCESS : Trie::Result::NOT_FOUND;
}
