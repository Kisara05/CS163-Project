#include "Core.h"

Core::Word::Word(const std::string& str) : orginalString(str), string(convertToNonAccentVN(str)) {
}

Core::Core(const std::string& inputDefCharSet, const std::string& inputSpecifier,
    const std::string& inputWordCharSet, const std::string& inputDataName) : dataSpecifier(inputSpecifier)
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

// Random tasks: 

Core::Word* Core::getRandomWord() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, wordCollection.size() - 1);
    int randomID = dist(gen);
    return wordCollection[randomID];
}

std::pair<Core::Word*, std::array<Core::Definition*, 5>> Core::getWordQuiz() {
    std::random_device rd;
    std::mt19937 gen(rd());

    // Create array of choices. Choice[0] is the answer.
    Definition* choices[5];
    // Get the random definition.
    Word* question = getRandomWord();
    std::uniform_int_distribution<> dist(0, question->defs.size() - 1);
    int randomID = dist(gen);
    choices[0] = question->defs[randomID];
    // Get the other 4 random definitions. One of them is the answer.
    std::uniform_int_distribution<> dist1(1, 4);
    randomID = dist1(gen);
    choices[randomID] = choices[0];
    for (int i = 1; i < 5; i++) {
        if (i != randomID) {
            Word* randomWord = getRandomWord();
            while (randomWord == question) {
                randomWord = getRandomWord();
            }
            std::uniform_int_distribution<> dist2(0,
                                                  randomWord->defs.size() - 1);
            int randomIndex2 = dist2(gen);
            choices[i] = randomWord->defs[randomIndex2];
        }
    }
    return std::make_pair(question, std::array<Definition*, 5>{choices[0], choices[1], choices[2], choices[3], choices[4]});
}

std::pair<Core::Definition*, std::array<Core::Word*, 5>> Core::getDefinitionQuiz() {
    // Get a definition.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, mDefCollection.size() - 1);
    int randomID = dist(gen);
    Definition* question = mDefCollection[randomID];
    // Create array of choices. Choice[0] is the answer.
    Word* choices[5];
    choices[0] = question->word;
    // Get the other 4 random words. One of them is the answer.
    std::uniform_int_distribution<> dist1(1, 4);
    randomID = dist1(gen);
    choices[randomID] = question->word;
    for (int i = 1; i < 5; i++) {
        if (i != randomID) {
            Word* randomWord = getRandomWord();
            while (randomWord == question->word) {
                randomWord = getRandomWord();
            }
            choices[i] = randomWord;
        }
    }
    return std::make_pair(question, std::array<Word*, 5>{choices[0], choices[1], choices[2], choices[3], choices[4]});
}

// End of Random tasks

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
        wordSet.remove(word -> string);
        for (int i = 0; i < word -> defs.size(); i++) {
            word -> defs[i] -> str = "";
        }
        word -> string = "";
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