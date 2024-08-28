#include "Dictionary.h"

Core Dictionary::CORE[] = {
    Core(
        "ENG-ENG", "engeng",
        " !\"#$%&\\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~",
        "abcdefghijklmnopqrstuvwxyz"),
    Core(
        "ENG-VIE", "engvie",
        " !\"#$%&\\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~",
        "abcdefghijklmnopqrstuvwxyz"),
    Core(
        "VIE-ENG", "vieeng",
        " !\"#$%&\\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~",
        "abcdefghijklmnopqrstuvwxyz"),
    Core(
        "SLANG", "slang",
        " !\"#$%&\\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~",
        "abcdefghijklmnopqrstuvwxyz"),
    Core(
        "EMOJI", "emoji",
        " !\"#$%&\\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~",
        "abcdefghijklmnopqrstuvwxyz")};

Dictionary& Dictionary::getInstance() {
    static Dictionary instance;
    return instance;
}

Core& Dictionary::getDict() {
    return *mCurDict;
}

void Dictionary::setDict(int index) {
    mCurDict = &CORE[index];
}

Dictionary::Dictionary()
: mCurDict(&CORE[0]) {
}

Dictionary::~Dictionary() {
}
