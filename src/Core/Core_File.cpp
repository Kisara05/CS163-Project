#include <filesystem>
#include <iostream>
#include <fstream>

#include "Core.h"

#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)

void Core::saveToFile() {
    std::filesystem::path dataPath("data");
    auto wordSetPath = dataPath / "local" / dataSpecifier / "data.json";

    nlohmann::json j = wordSet;
    std::ofstream wordSetFile(wordSetPath);
    wordSetFile << j;
    wordSetFile.close();

    auto defWordSetPath = dataPath / "local" / dataSpecifier / "defword.json";
    std::ofstream defWordSetFile(defWordSetPath);
    j = defWordSet;
    defWordSetFile << j;
    defWordSetFile.close();
}

void Core::loadFromFile() {
    std::filesystem::path dataPath("data");
    auto wordSetPath = dataPath / "local" / dataSpecifier / "data.json";

    std::ifstream wordSetFile(wordSetPath);
    nlohmann::json j = nlohmann::json::parse(wordSetFile);
    wordSet = j.template get<Trie<Word>>();
    wordSetFile.close();

    auto defWordSetPath = dataPath / "local" / dataSpecifier / "defword.json";
    std::ifstream defWordSetFile(defWordSetPath);
    nlohmann::json j = nlohmann::json::parse(defWordSetFile);
    defWordSet = j.template get<Trie<DefWord>>();
    defWordSetFile.close();
}
