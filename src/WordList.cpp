#include "WordList.h"

WordList::WordList(const std::vector<Core::Word*>& list)
: mList(list) {
    mRowHeight = 65;
    for (int i = 0; i < mList.size(); i++) {
        createNewButton();
    }
    
}

WordList::~WordList() {
}

void WordList::update(float dt) {
    mPositionY += (GetMouseWheelMove() * 20);
    if (mPositionY + mRowHeight * mList.size() < mRect.height) {
        mPositionY = mRect.height - mRowHeight * mList.size();
    }
    if (mPositionY > 0) {
        mPositionY = 0;
    }

    if (mButtonList.size() > mList.size())
        mButtonList.pop_back();
    else {
        for (int i = 0; i < mList.size(); i++) {
            if (i >= mButtonList.size()) {
                createNewButton();
            }
            float startingPosY = mRect.y + mPositionY + i * mRowHeight;
            mButtonList[i]->setRect(
                {mRect.x, startingPosY, mRect.width, mRowHeight - 1});
            mButtonList.back()->setCallback([this, i]() {
                this->mInfoPage.setWord(this->mList[i]);
            });

            if (mInfoPage.isActivated() ||  startingPosY < mRect.y
                || startingPosY + mRowHeight > mRect.y + mRect.height) {
                mButtonList[i]->deactivate();
            } else {
                mButtonList[i]->activate();
            }
        }
    }
    for (auto buttonPtr : mButtonList) {
        buttonPtr->update(dt);
    }
    mInfoPage.update(dt);
}

void WordList::draw() {
    BeginScissorMode(mRect.x, mRect.y, mRect.width, mRect.height);
    for (auto buttonPtr : mButtonList) {
        buttonPtr->draw();
    }
    for (int i = 0; i < mList.size(); i++) {
        float startingPosY = mRect.y + mPositionY + i * mRowHeight;
        TextBox wordText(mList[i]->orgStr, {mRect.x + 35, startingPosY + 7,
                                            mRect.width, mRowHeight});
        wordText.setBorderColor(BLANK);
        wordText.setColor(BLANK);
        wordText.setTextSize(32);
        wordText.makeShort();
        wordText.draw();
        DrawLineEx({mRect.x, startingPosY + mRowHeight},
                   {mRect.x + mRect.width, startingPosY + mRowHeight}, 0.5,
                   AppColor::TEXT);
    }
    EndScissorMode();
    mInfoPage.draw();
}

void WordList::setRect(Rectangle rect) {
    mRect = rect;
    mInfoPage.setRect(mRect);
}

void WordList::setWord(Core::Word* word) {
    mInfoPage.setWord(word);
}

void WordList::resetPosition() {
    mPositionY = 0;
}

void WordList::createNewButton() {
    mButtonList.push_back(std::make_unique<Button>());
    mButtonList.back()->setColor(AppColor::BACKGROUND_1);
    mButtonList.back()->setBorderThickness(0);
    mButtonList.back()->setCornerRoundness(0);
}
