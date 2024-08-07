#ifndef CORE_CORE_H
#define CORE_CORE_H

#include "Trie.h"

class Core {
public:
    static constexpr int RESULT_LIMIT = 20;

    struct Word;


    void addFavorite(Word* word);
    void removeFavorite(Word* word);
    bool isFavorite(Word* word);


private:

#endif // CORE_CORE_H