#include "Trie.h"
#include <functional>

TRIE_TEMPLATE
Trie<T>::Node::Node() : data(nullptr), isEnd(false) {}

TRIE_TEMPLATE
Trie<T>::Node::Node(T *data, bool isEnd) : data(data), isEnd(isEnd) {}

TRIE_TEMPLATE
Trie<T>::Node::~Node() {
  if (data)
    delete data;
  children.clear();
}

TRIE_TEMPLATE
Trie<T>::Trie() : root(new Node()) {}

TRIE_TEMPLATE
Trie<T>::~Trie() {
  if (root)
    delete root;
}

TRIE_TEMPLATE
typename Trie<T>::Result Trie<T>::insert(T *data) {
  if (!data)
    return Trie::Result::FAILED;
  std::string word = data->getWord();
  if (word.empty())
    return Trie::Result::FAILED;
  return insert(word, data);
}

TRIE_TEMPLATE
typename Trie<T>::Result Trie<T>::insert(std::string word) {
  return insert(word, new T(word));
}

TRIE_TEMPLATE
typename Trie<T>::Result Trie<T>::insert(std::string word, T *data) {
  if (word == "")
    return Trie::Result::EMPTY_STRING;
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
  current->data = data;
  return Trie::Result::SUCCESS;
}

TRIE_TEMPLATE
typename Trie<T>::Result Trie<T>::remove(std::string word) {
  if (word == "")
    return Trie::Result::EMPTY_STRING;
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
  if (current->data)
    delete current->data;
  return Trie::Result::SUCCESS;
}

TRIE_TEMPLATE
typename Trie<T>::Result Trie<T>::contains(std::string word) {
  if (word == "")
    return Trie::Result::EMPTY_STRING;
  Node *current = root;
  for (char c : word) {
    if (current->children.count(c) == 0) {
      return Trie::Result::NOT_FOUND;
    }
    current = current->children[c];
  }
  return current->isEnd ? Trie::Result::SUCCESS : Trie::Result::NOT_FOUND;
}

TRIE_TEMPLATE
T *Trie<T>::find(std::string word) {
  Node *current = root;
  for (char c : word) {
    if (current->children.count(c) == 0) {
      return nullptr;
    }
    current = current->children[c];
  }
  return current->data;
}

TRIE_TEMPLATE
std::vector<T *> Trie<T>::startsWith(std::string prefix) {
  if (prefix == "")
    return {};
  std::vector<T *> result;
  Node *current = root;
  for (char c : prefix) {
    if (current->children.count(c) == 0) {
      return result;
    }
    current = current->children[c];
  }
  std::function<void(Node *)> dfs = [&](Node *node) -> void {
    if (node->isEnd) {
      result.push_back(node->data);
    }
    for (auto &[ch, child] : node->children) {
      dfs(child);
    }
  };
  dfs(current);
  return result;
}

TRIE_TEMPLATE
void Trie<T>::clear() {
  if (root)
    delete root;
  root = new Node();
}