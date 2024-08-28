#ifndef CORE_CORE_H
#define CORE_CORE_H

#include "Trie.h"
#include "nlohmann/json.hpp"
#include <array>
#include <fstream>
#include <random>
#include <string>
#include <vector>

class Core {
public:
  static constexpr int RESULT_LIMIT = 20;

  struct Word;

  struct Definition {
    std::string originalString;
    std::string str;
    Word *word;

    int rating;

    explicit Definition() = default;
    Definition(const std::string &str);

    bool isDeleted();

  public:
    friend void from_json(const nlohmann::json &j, Definition &d) {
      j.at("originalString").get_to(d.originalString);
      j.at("str").get_to(d.str);
      d.word = nullptr;
    }

    friend void to_json(nlohmann::json &j, const Definition &d) {
      j["originalString"] = d.originalString;
      j["string"] = d.str;
    }
  };

  struct Word {
    std::string originalString;
    std::string string;
    std::vector<Definition *> defs;
    bool IsFavorite{false};
    Word(const std::string &str);

    bool isDeleted();

  public:
    friend void from_json(const nlohmann::json &j, Word &w) {
      j.at("orginalString").get_to(w.originalString);
      j.at("string").get_to(w.string);
      j.at("IsFavorite").get_to(w.IsFavorite);

      for (auto def : j.at("defs")) {
        Core::Definition* d = new Definition;
        def.get_to(*d);
        d->word = &w;
        w.defs.push_back(d);
      }
    }

    friend void to_json(nlohmann::json &j, const Word &w) {
      j["orginalString"] = w.originalString;
      j["string"] = w.string;
      j["IsFavorite"] = w.IsFavorite;

      for (auto def : w.defs) {
        j["defs"].push_back(*def);
      }
    }
  };

  struct DefWord {
    std::string str;
    std::vector<Definition*> defs;
    DefWord(const std::string &str);

  public:
    friend void from_json(const nlohmann::json &j, DefWord &dw) {
      j.at("str").get_to(dw.str);

      for (auto def : j.at("defs")) {
        Core::Definition* d = new Definition;
        def.get_to(*d);
        dw.defs.push_back(d);
      }
    }

    friend void to_json(nlohmann::json &j, const DefWord &dw) {
      j["str"] = dw.str;

      for (auto def : dw.defs) {
        j["defs"].push_back(*def);
      }
    }
  };

  Core(const std::string &dataName, const std::string &specifier,
       const std::string &wordCharSet, const std::string &defCharSet);
  ~Core();
  std::vector<Word *> searchKeyword(const std::string &inputString);
  std::vector<Word *> searchDefinition(const std::string &inputString);
  Word *getRandomWord();
  Definition *addDefinition(std::string defString, Word *word);
  void editDefinition(Definition *def, const std::string &newDef);
  void addFavorite(Word *word);
  void removeFavorite(Word *word);
  bool isFavorite(Word *word);
  void loadDataFromSpecifier(const std::string &dataSpecifier,
                             std::vector<std::string> &word);
  void loadDataFromHistory(const std::string &dataSpecifier);
  void loadWordLocal(const std::string &dataSpecifier);
  std::string extractFirstWord(const std::string &inputString);
  std::string extractSecondWord(const std::string &inputString);
  void updateHistory(Word *word);
  std::vector<Word *> getHistory();
  std::vector<Core::Word *> getFavoriteList();

  // pair::first is the question, pair::second [1..4] are choices, [0] is the
  // answer
  std::pair<Word *, std::array<Definition *, 5>> getWordQuiz();
  std::pair<Definition *, std::array<Word *, 5>> getDefinitionQuiz();

  Word *addWord(std::string wordToBeAdded);
  std::string getDataName();
  void removeWord(Word *word);

  void resetDefault();

private:
  // Random tasks:
  std::vector<Word *> wordCollection;
  std::vector<Definition *> defCollection;
  std::vector<DefWord *> defWordCollection;
  // End of random tasks

  std::vector<Word *> history;

  Trie<Word> wordSet;
  Trie<DefWord> defWordSet;

  std::string dataName;
  std::string dataSpecifier;
  void loadFromFile();
  void saveToFile();
  void ratingCleanUp();
  void equivalentFilter1(std::vector<Definition *> &defResults, const std::string &inputString);
  void equivalentFilter2(std::vector<Definition *> &defResults, const std::string &inputString);
};
#endif // CORE_CORE_H
