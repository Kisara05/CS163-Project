#include "../src/Core/Data.cpp"
#include "../src/Core/Data.h"
#include "../src/Core/Trie.cpp"
#include "../src/Core/Trie.h"

#include "gtest/gtest.h"
#include <algorithm>

#define SC Trie::Result::SUCCESS
#define NF Trie::Result::NOT_FOUND
#define AE Trie::Result::ALREADY_EXISTS
#define E Trie::Result::EMPTY_STRING
#define F Trie::Result::FAILED

TEST(TrieTest, InsertAndContains) {
  Trie trie;

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
  Trie trie;

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

  Trie trie;

  // Insert and remove
  for (int i = 1; i <= 10000; i++) {
    ASSERT_EQ(trie.insert(std::to_string(i)), SC);
  }
  for (int i = 1; i <= 10000; i++) {
    ASSERT_EQ(trie.remove(std::to_string(i)), SC);
  }
  for (int i = 1; i <= 10000; i++) {
    ASSERT_EQ(trie.contains(std::to_string(i)), NF);
  }
}

TEST(TrieTest, FIND) {
  Trie trie;

  // Test with normal string
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
  Trie trie;

  // Test with normal string
  ASSERT_EQ(trie.insert("hello"), SC);
  ASSERT_EQ(trie.insert("hello world"), SC);
  ASSERT_EQ(trie.insert("hello world!"), SC);
  ASSERT_EQ(trie.insert("hello world!"), AE);

  std::vector<Data *> found = trie.startsWith("hello");
  std::sort(found.begin(), found.end(),
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
  std::sort(found.begin(), found.end(),
            [](Data *a, Data *b) { return a->getWord() < b->getWord(); });
  ASSERT_EQ(found.size(), 2);
  ASSERT_EQ(found[0]->getWord(), "@#$%^&*()");
  ASSERT_EQ(found[1]->getWord(), "@#$%^&*()!");
}
