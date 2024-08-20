#include "../src/Core/Trie.h"

#include "gtest/gtest.h"
#include <algorithm>

class Data {
public:
  Data();
  Data(std::string word);
  virtual ~Data();
  virtual std::string getWord();
  std::string word;
};

class Word : Data {
public:
  Word();
  Word(std::string word);
  ~Word();
};
Data::Data() : word("") {}
Data::Data(std::string word) : word(word) {}
Data::~Data() {}

std::string Data::getWord() { return word; }

Word::Word() : Data() {}
Word::Word(std::string word) : Data(word) {}
Word::~Word() {}

using namespace std;

#define SC Trie<Data>::Result::SUCCESS
#define NF Trie<Data>::Result::NOT_FOUND
#define AE Trie<Data>::Result::ALREADY_EXISTS
#define E Trie<Data>::Result::EMPTY_STRING
#define F Trie<Data>::Result::FAILED

TEST(TrieTest, InsertAndContains) {
  Trie<Data> trie;

  // Test with normal string
  ASSERT_EQ(trie.insert("hello"), SC);
  ASSERT_EQ(trie.contains("hello"), SC);

  // Test with empty string
  ASSERT_EQ(trie.insert(""), E);
  ASSERT_EQ(trie.contains(""), E);

  // Test with special characters
  ASSERT_EQ(trie.insert("@#$%^&*()"), SC);
  ASSERT_EQ(trie.contains("@#$%^&*()"), SC);

  // Test with large input
}

TEST(TrieTest, Remove) {
  Trie<Data> trie;

  // Test with normal string
  ASSERT_EQ(trie.insert("hello"), SC);
  ASSERT_EQ(trie.remove("hello"), SC);
  ASSERT_EQ(trie.remove("hello"), NF);
  ASSERT_EQ(trie.contains("hello"), NF);

  // Test with empty string
  ASSERT_EQ(trie.insert(""), E);
  ASSERT_EQ(trie.remove(""), E);
  ASSERT_EQ(trie.contains(""), E);

  // Test with special characters
  ASSERT_EQ(trie.insert("@#$%^&*()"), SC);
  ASSERT_EQ(trie.remove("@#$%^&*()"), SC);
  ASSERT_EQ(trie.contains("@#$%^&*()"), NF);
}

TEST(TrieTest, LARGE_TEST_CASE) {

  Trie<Data> trie;

  // Insert and remove
  for (int i = 1; i <= 10000; ++i)
    ASSERT_EQ(trie.insert(to_string(i)), SC);
  for (int i = 1; i <= 10000; ++i)
    ASSERT_EQ(trie.remove(to_string(i)), SC);
  for (int i = 1; i <= 10000; ++i)
    ASSERT_EQ(trie.contains(to_string(i)), NF);
}

TEST(TrieTest, FIND) {
  Trie<Data> trie;

  // Test wit h normal string
  ASSERT_EQ(trie.insert("hello"), SC);
  Data *found = trie.find("hello");
  ASSERT_NE(found, nullptr);
  ASSERT_EQ(found->getWord(), "hello");

  // Test with empty string
  ASSERT_EQ(trie.insert(""), E);
  ASSERT_EQ(trie.find(""), nullptr);

  // Test with special characters
  ASSERT_EQ(trie.insert("@#$%^&*()"), SC);
  ASSERT_EQ(trie.find("@#$%^&*()")->getWord(), "@#$%^&*()");
}

TEST(TrieTest, STARTSWITH) {
  Trie<Data> trie;

  // Test with normal string
  ASSERT_EQ(trie.insert("hello"), SC);
  ASSERT_EQ(trie.insert("hello world"), SC);
  ASSERT_EQ(trie.insert("hello world!"), SC);
  ASSERT_EQ(trie.insert("hello world!"), AE);

  vector<Data *> found = trie.startsWith("hello");
  sort(found.begin(), found.end(),
       [](Data *a, Data *b) { return a->getWord() < b->getWord(); });
  ASSERT_EQ(found.size(), 3);
  ASSERT_EQ(found[0]->getWord(), "hello");
  ASSERT_EQ(found[1]->getWord(), "hello world");
  ASSERT_EQ(found[2]->getWord(), "hello world!");

  // trie.clear();

  // Test with empty string
  ASSERT_EQ(trie.insert(""), E);
  ASSERT_EQ(trie.startsWith("").size(), 0);
  trie.clear();

  // Test with special characters
  ASSERT_EQ(trie.insert("@#$%^&*()"), SC);
  ASSERT_EQ(trie.insert("@#$%^&*()!"), SC);
  ASSERT_EQ(trie.insert("@#$%^&*()!"), AE);

  found = trie.startsWith("@#$%^&*()");
  sort(found.begin(), found.end(),
       [](Data *a, Data *b) { return a->getWord() < b->getWord(); });
  ASSERT_EQ(found.size(), 2);
  ASSERT_EQ(found[0]->getWord(), "@#$%^&*()");
  ASSERT_EQ(found[1]->getWord(), "@#$%^&*()!");
}
