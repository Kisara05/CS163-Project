#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "Core.h"

// Singleton
class Dictionary {
public:
    static Core CORE[];

public:
    static Dictionary& getInstance();

    Core& getDict();
    
    void setDict(int index);

private:
    Dictionary();
    Dictionary(Dictionary const&) = delete;
    void operator= (Dictionary const&) = delete;
    ~Dictionary();

private:
    Core* mCurDict;
};

#endif // DICTIONARY_H
