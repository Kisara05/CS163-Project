#include "Core.h"

Core::Word::Word(const std::string& str) : orgStr(str), str(convertToNonAccentVN(str)) {
}

Core::Core(const std::string& inputDefCharSet, const std::string& inputSpecifier,
    const std::string& inputWordCharSet, const std::string& inputDataName)
    : dataSpecifier(inputSpecifier)
    , dataName(inputDataName)
    , defWordSet(inputDefCharSet)
    , wordSet(inputWordCharSet) {
    std::cout << "Now loading: " << dataSpecifier << "..." << std::endl;
    loadFromFile();
}

bool Core::Word::isDeleted() {
    //delete this string
    return string == "";
}

Core::Word* Core::getRandomWord() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, wordCollection.size() - 1);
    int randomID = dist(gen);
    return wordCollection[randomID];
}


void Core::addFavorite(Word* word) {
    if (word->IsFavorite == false) {
        word->IsFavorite = true;
    }
    else {
        std::cout << "You have already added this favorite word." << std::endl;
        return;
    }
}

void Core::removeFavorite(Word* word) {
    if (word->IsFavorite == true) {
        word->IsFavorite = false;
    }
    else {
        std::cout << "This has yet been added as favorite word." << std::endl;
        return;
    }
}

bool Core::isFavorite(Word* word) {
    // Check if is favorite
    return word->IsFavorite;
}

std::string Core::getDataName() {
    return dataName;
}

Core::Word* Core::addWord(std::string wordToBeAdded) {
    Word* newWord = new Word(wordToBeAdded);
    if (wordSet.insert(newWord) == Trie<Word*>::StatusID::SUCCESS) {
        wordCollection.push_back(newWord);
    }
    else {
        delete newWord;
        newWord = nullptr;
    }
    return newWord;
}

void Core::removeWord(Word* word) {
    if (word != nullptr) {
        wordSet.remove(word -> str);
        for (int i = 0; i < word -> defs.size(); i++) {
            word -> defs[i] -> str = "";
        }
        word -> str = "";
    }
}

Core::~Core() {
    saveToFile();

    for (auto ptr : wordCollection) {
        delete ptr;
    }
    for (auto ptr : mDefCollection) {
        delete ptr;
    }
    for (auto ptr : mDefWordCollection) {
        delete ptr;
    }
}