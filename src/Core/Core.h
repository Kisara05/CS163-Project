#ifndef CORE_CORE_H
#define CORE_CORE_H

#include "Trie.h"
#include <random>

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

    Word *getRandomWord();

    void addFavorite(Word* word);
    void removeFavorite(Word* word);
    bool isFavorite(Word* word);

    Word* addWord(std::string wordToBeAdded);

private:
    std::vector<Word *> mWordCollection;
    
};
#endif // CORE_CORE_H