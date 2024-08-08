#ifndef CORE_CORE_H
#define CORE_CORE_H

#include "Trie.h"
#include <random>
#include <vector>
#include <string>

class Core {
public:
    static constexpr int RESULT_LIMIT = 20;

    struct Word;

    struct Definition {
        std::string orgStr;
        std::string str;
        Word *word;

        int rating;

        Definition(const std::string &str);

        bool isDeleted();
    };

    struct Word {
        std::string orginalString;
        std::string string;
        std::vector<Definition*> defs;
        bool IsFavorite{ false };
        Word(const std::string& str);

        bool isDeleted();
    };

    Core(const std::string& dataName, const std::string& specifier,
        const std::string& wordCharSet, const std::string& defCharSet);
    ~Core();

    Word *getRandomWord();

    void addFavorite(Word* word);
    void removeFavorite(Word* word);
    bool isFavorite(Word* word);

    Word* addWord(std::string wordToBeAdded);
    std::string getDataName();
    void removeWord(Word* word);

private:
    std::vector<Word *> wordCollection;

    Trie<Word*> wordSet;
    Trie<DefWord*> defWordSet;

    std::string dataName;
    std::string dataSpecifier;
    
};
#endif // CORE_CORE_H