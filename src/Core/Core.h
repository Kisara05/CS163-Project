#ifndef CORE_CORE_H
#define CORE_CORE_H

#include "Trie.h"
#include <random>
#include <vector>
#include <string>
#include <array>

class Core {
public:
    static constexpr int RESULT_LIMIT = 20;

    struct Word;

    struct Definition {
        std::string originalString;
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

    struct DefWord {
        std::string str;
        std::vector<Definition *> defs;
        DefWord(const std::string &str);
    };

    Core(const std::string& dataName, const std::string& specifier,
        const std::string& wordCharSet, const std::string& defCharSet);
    ~Core();
    std::vector<Word *> searchKeyword(const std::string &inputString);
    std::vector<Word *> searchDefinition(const std::string &inputString);
    Word *getRandomWord();
    Definition *addDefinition(std::string defString, Word *word);
    void editDefinition(Definition *def, const std::string &newDef);
    void addFavorite(Word* word);
    void removeFavorite(Word* word);
    bool isFavorite(Word* word);

    // pair::first is the question, pair::second [1..4] are choices, [0] is the
    // answer
    std::pair<Word *, std::array<Definition *, 5>> getWordQuiz();
    std::pair<Definition *, std::array<Word *, 5>> getDefinitionQuiz();

    Word* addWord(std::string wordToBeAdded);
    std::string getDataName();
    void removeWord(Word* word);

    void resetDefault();

private:
    // Random tasks: 
    std::vector<Word *> wordCollection;
    std::vector<Definition *> mDefCollection;
    std::vector<DefWord *> mDefWordCollection;
    // End of random tasks

    Trie<Word> wordSet;
    Trie<DefWord> defWordSet;

    std::string dataName;
    std::string dataSpecifier;

    void loadFromFile();
    void saveToFile();
    
};
#endif // CORE_CORE_H
