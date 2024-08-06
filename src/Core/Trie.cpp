#include "Trie.h"
#include <functional>

Trie::Node::Node() : data(nullptr), isEnd(false) {}
Trie::Node::Node(Data *data, bool isEnd) : data(data), isEnd(isEnd) {}
Trie::Node::~Node() {
  if (data)
    delete data;
  // children.clear();
}
Trie::Trie() : root(new Node()) {}
Trie::~Trie() {
  if (root)
    delete root;
}

Trie::Result Trie::insert(Data *data) {
  if (!data)
    return Trie::Result::FAILED;
  std::string word = data->getWord();
  if (word.empty())
    return Trie::Result::FAILED;
  return insert(word, data);
}

Trie::Result Trie::insert(std::string word) {
  return insert(word, new Data(word));
}

Trie::Result Trie::insert(std::string word, Data *data) {
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

Trie::Result Trie::remove(std::string word) {
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

Trie::Result Trie::contains(std::string word) {
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

Data *Trie::find(std::string word) {
  Node *current = root;
  for (char c : word) {
    if (current->children.count(c) == 0) {
      return nullptr;
    }
    current = current->children[c];
  }
  return current->data;
}

std::vector<Data *> Trie::startsWith(std::string prefix) {
  if (prefix == "")
    return {};
  std::vector<Data *> result;
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

void Trie::clear() {
  if (root)
    delete root;
  root = new Node();
}
