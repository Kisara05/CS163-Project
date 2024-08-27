#ifndef WORDINFO_H
#define WORDINFO_H

#include "Core/Core.h"
#include "Core/Dictionary.h"
#include "GUIComponents/Button.h"
#include "GUIComponents/InputBox.h"
#include "GUIComponents/TextBox.h"

#include "raylib.h"

class WordInfo {
public:
    WordInfo();
    ~WordInfo();

    void update(float dt);
    void draw();

    void setRect(Rectangle rect);

    void setWord(Core::Word* word);

    bool isActivated();

private:
    Core::Word* mWord{nullptr};

    Rectangle mRect;

    Button mStarButton;
    Button mDeleteButton;

    Button mReturnButton;
    Button mEditButton;
    Button mCancelButton;
    Button mSaveButton;

    float mPositionY{0};

    bool mEditMode{false};
    std::vector<InputBox::Ptr> mDefEdittors;
    Button mAddDefBtn;

private:
    void drawDefinitions();

    void updateInfoMode(float dt);
    void updateEditMode(float dt);

    void drawInfoMode();
    void drawEditMode();

    void addEdittors();
    void saveEdittors();
    void addOneEdittor(const std::string& str);
};

#endif // WORDINFO_H
