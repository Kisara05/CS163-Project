#ifndef WORDLIST_H
#define WORDLIST_H

#include "Core/Core.h"
#include "GUIComponents/Button.h"
#include "GUIComponents/TextBox.h"
#include "WordIn4.h"

#include "raylib.h"

class WordList {
public:
    WordList(const std::vector<Core::Word *> &list);
    ~WordList();

    void update(float dt);
    void draw();

    void setRect(Rectangle rect);

    void setWord(Core::Word* word);
    void resetPosition();

private:
    void createNewButton();

private:
    const std::vector<Core::Word*> &mList;
    std::vector<Button::SmartPointer> mButtonList;

    Rectangle mRect;
    float mRowHeight;

    bool mIsHistory{false};

    float mPositionY{0};

    WordInfo mInfoPage;
};

#endif // WORDLIST_H
