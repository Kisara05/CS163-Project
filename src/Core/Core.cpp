#include "Core.h"

Core::Word::Word(const std::string& str) : orgStr(str), str(convertToNonAccentVN(str)) {
}

bool Core::Word::isDeleted() {
    //delete this string
    return string == "";
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