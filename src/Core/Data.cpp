#include "Data.h"
#include <string>
Data::Data() : word("") {}
Data::Data(std::string word) : word(word) {}
Data::~Data() {}

std::string Data::getWord() { return word; }

Word::Word() : Data() {}
Word::Word(std::string word) : Data(word) {}
Word::~Word() {}
