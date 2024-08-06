#include "../src/Core/Trie.cpp"
#include "../src/Core/Trie.h"

#include "gtest/gtest.h"

#define SC Trie::Result::SUCCESS
#define NF Trie::Result::NOT_FOUND
#define AE Trie::Result::ALREADY_EXISTS

TEST(TrieTest, InsertAndSearch) {
  Trie trie;

  ASSERT_EQ(trie.insert("hello"), SC);

  ASSERT_EQ(trie.insert("hello"), AE);

  ASSERT_EQ(trie.search("hello"), SC);

  ASSERT_EQ(trie.search("world"), NF);
}

TEST(TrieTest, InsertAndRemove) {
  Trie trie;

  ASSERT_EQ(trie.insert("hello"), SC);

  ASSERT_EQ(trie.remove("hello"), SC);

  ASSERT_EQ(trie.remove("hello"), NF);

  ASSERT_EQ(trie.search("hello"), NF);
}

TEST(TrieTest, InsertAndRemovePrefix) {
  Trie trie;

  ASSERT_EQ(trie.insert("hello"), SC);

  ASSERT_EQ(trie.insert("hell"), SC);

  ASSERT_EQ(trie.search("hello"), SC);

  ASSERT_EQ(trie.search("hell"), SC);

  ASSERT_EQ(trie.remove("hell"), SC);

  ASSERT_EQ(trie.search("hello"), SC);

  ASSERT_EQ(trie.search("hell"), NF);
}
