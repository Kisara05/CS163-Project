#include "WordInfo.h"

WordInfo::WordInfo() {
    mStarButton.setRect({946, 196, 33, 33});
    mStarButton.setBorderThickness(0);
    mStarButton.setColor(BLANK);
    mStarButton.setCallback([this]() {
        if (this->mWord == nullptr)
            return;
        if (Dictionary::getInstance().getDict().isFavorite(this->mWord)) {
            Dictionary::getInstance().getDict().removeFavorite(this->mWord);
            this->mStarButton.setTexture(
                TextureHolder::getInstance().get(TextureID::StarUnselected));
        } else {
            Dictionary::getInstance().getDict().addFavorite(this->mWord);
            this->mStarButton.setTexture(
                TextureHolder::getInstance().get(TextureID::StarSelected));
        }
    });

    mDeleteButton.setRect({872, 196, 33, 33});
    mDeleteButton.setTexture(TextureHolder::getInstance().get(TextureID::Delete));
    mDeleteButton.setBorderThickness(0);
    mDeleteButton.setColor(BLANK);
    mDeleteButton.setCallback([this]() {
        Dictionary::getInstance().getDict().removeWord(this->mWord);
        this->mWord = nullptr;
    });

    mReturnButton.setRect({341, 532, 75, 75});
    mReturnButton.setBorderThickness(0);
    mReturnButton.setColor(BLANK);
    mReturnButton.setTexture(
        TextureHolder::getInstance().get(TextureID::Return));
    mReturnButton.setCallback([this]() {
        this->mWord = nullptr;
    });

    mEditButton.setRect({916, 532, 75, 75});
    mEditButton.setBorderThickness(0);
    mEditButton.setColor(BLANK);
    mEditButton.setTexture(TextureHolder::getInstance().get(TextureID::Edit));
    mEditButton.setCallback([this]() {
        this->mEditMode = true;
        this->addEdittors();
    });

    mCancelButton.setRect({816, 532, 75, 75});
    mCancelButton.setBorderThickness(0);
    mCancelButton.setColor(BLANK);
    mCancelButton.setTexture(
        TextureHolder::getInstance().get(TextureID::Cancel));
    mCancelButton.setCallback([this]() {
        this->mEditMode = false;
    });

    mSaveButton.setRect({916, 532, 75, 75});
    mSaveButton.setBorderThickness(0);
    mSaveButton.setColor(BLANK);
    mSaveButton.setTexture(TextureHolder::getInstance().get(TextureID::Save));
    mSaveButton.setCallback([this]() {
        this->mEditMode = false;
        this->saveEdittors();
    });

    mAddDefBtn.setSize({637, 74});
    mAddDefBtn.setBorderThickness(0);
    mAddDefBtn.setColor(BLANK);
    mAddDefBtn.setTexture(
        TextureHolder::getInstance().get(TextureID::AddDefinition));
    mAddDefBtn.setCallback([this]() {
        this->addOneEdittor("");
    });
}

WordInfo::~WordInfo() {
}

void WordInfo::update(float dt) {
    if (mWord == nullptr)
        return;

    mStarButton.update(dt);
    mDeleteButton.update(dt);

    mPositionY += (GetMouseWheelMove() * 20);

    if (mPositionY > 0) {
        mPositionY = 0;
    }

    if (mEditMode) {
        updateEditMode(dt);
    } else {
        updateInfoMode(dt);
    }
}

void WordInfo::draw() {
    if (mWord == nullptr)
        return;

    DrawRectangleRec(mRect, AppColor::BACKGROUND_1);

    TextBox wordText(mWord->orgStr, {mRect.x + 13, mRect.y + 2, 508, 72});
    wordText.setTextSize(62);
    wordText.setBorderColor(BLANK);
    wordText.setColor(BLANK);
    wordText.makeShort();
    wordText.draw();

    mStarButton.draw();
    mDeleteButton.draw();

    drawDefinitions();

    if (mEditMode) {
        mCancelButton.draw();
        mSaveButton.draw();
    } else {
        mReturnButton.draw();
        mEditButton.draw();
    }
}

void WordInfo::setRect(Rectangle rect) {
    mRect = rect;
}

void WordInfo::setWord(Core::Word* word) {
    if (word == nullptr) return;
    Dictionary::getInstance().getDict().updateHistory(word);
    mWord = word;
    mPositionY = 0;
    if (Dictionary::getInstance().getDict().isFavorite(mWord)) {
        mStarButton.setTexture(
            TextureHolder::getInstance().get(TextureID::StarSelected));
    } else {
        mStarButton.setTexture(
            TextureHolder::getInstance().get(TextureID::StarUnselected));
    }
}

bool WordInfo::isActivated() {
    return mWord != nullptr;
}

void WordInfo::drawDefinitions() {
    BeginScissorMode(341, 279, 641, 361);

    if (mEditMode) {
        drawEditMode();
    } else {
        drawInfoMode();
    }
    EndScissorMode();
}

void WordInfo::updateInfoMode(float dt) {
    mReturnButton.update(dt);
    mEditButton.update(dt);
}

void WordInfo::updateEditMode(float dt) {
    mAddDefBtn.update(dt);

    float startingPosY = 282 + mPositionY;
    for (int i = 0; i < mDefEdittors.size(); i++) {
        mDefEdittors[i]->setRect({343, startingPosY, 637, 0});

        if (startingPosY < 282) {
            mDefEdittors[i]->deactivateClickability();
        } else {
            mDefEdittors[i]->activateClickability();
        }
        mDefEdittors[i]->update(dt);
        mDefEdittors[i]->setCornerRoundness(20 * 2
                                            / mDefEdittors[i]->getHeight());
        startingPosY += mDefEdittors[i]->getHeight() + 20;
    }
    mAddDefBtn.setPosition({343, startingPosY});

    mCancelButton.update(dt);
    mSaveButton.update(dt);
}

void WordInfo::drawInfoMode() {
    float startingPosY = 279 + mPositionY;
    int cnt = 0;
    for (auto defPtr : mWord->defs) {
        if (defPtr->isDeleted())
            continue;
        cnt++;
        TextBox wordText(std::to_string(cnt) + ". " + defPtr->orgStr,
                         {358, startingPosY, 616, 1});
        wordText.setBorderColor(BLANK);
        wordText.setColor(BLANK);
        wordText.setTextSize(22);
        wordText.draw();

        startingPosY += wordText.getHeight();
    }
}

void WordInfo::drawEditMode() {
    for (auto inputPtr : mDefEdittors) {
        inputPtr->draw();
    }
    mAddDefBtn.draw();
}

void WordInfo::addEdittors() {
    mDefEdittors.clear();
    for (int i = 0; i < mWord->defs.size(); i++) {
        if (mWord->defs[i]->isDeleted())
            continue;
        addOneEdittor(mWord->defs[i]->orgStr);
    }
}

void WordInfo::saveEdittors() {
    int defSize = mWord->defs.size();
    int j = 0; // Iterator for defs cuz some of the defs maybe deleted (emptry
               // string)
    for (int i = 0; i < mDefEdittors.size(); i++) {
        while (j < defSize && mWord->defs[j]->isDeleted()) j++;
        if (j < defSize) {
            Dictionary::getInstance().getDict().editDefinition(
                mWord->defs[j], mDefEdittors[i]->getInputText());
        } else {
            Dictionary::getInstance().getDict().addDefinition(
                mDefEdittors[i]->getInputText(), mWord);
        }
    }
}

void WordInfo::addOneEdittor(const std::string& str) {
    mDefEdittors.push_back(std::make_unique<InputBox>(str));
    mDefEdittors.back()->setColor(AppColor::BACKGROUND_1);
    mDefEdittors.back()->setWrapped();
    mDefEdittors.back()->setTextSize(22);
    mDefEdittors.back()->setBorderThickness(1);
}
