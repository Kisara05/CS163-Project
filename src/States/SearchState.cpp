#include "SearchState.h"

#include "raylib.h"

#include <cassert>
#include <iostream>

SearchState::SearchState(StateStack &stack, Context context)
: State(stack, context)
, mScrollList(mWordList) {
    mNavBar.setCurNav(NavBar::NavID::Search);

    // Search bar
    mSearchBar.setRect({334, 99, 456, 40});
    mSearchBar.setPlaceHolder("Type Something...");
    mSearchBar.setTextSize(24);
    mSearchBar.setBorderColor(BLANK);

    // Search button
    mSearchButton.setRect({859, 99, 123, 40});
    mSearchButton.setText("Search");
    mSearchButton.setTextSize(24);
    mSearchButton.setContentColor(AppColor::TEXT_CONTRAST);
    mSearchButton.setColor(AppColor::PRIMARY);
    mSearchButton.setCornerRoundness(0.6);
    mSearchButton.setCallback([this]() {
        if (this->mSearchBar.getInputText() == "") {
            this->mScrollList.setWord(
                Dictionary::getInstance().getDict().getRandomWord());
            return;
        }
        if (this->mIsDefinitionSearch) {
            this->mWordList =
                Dictionary::getInstance().getDict().searchDefinition(
                    this->mSearchBar.getInputText());
        } else {
            // this->mWordList =
            // Dictionary::getInstance().getDict().searchKeyword(
            //     this->mSearchBar.getInputText());
            if (!this->mWordList.empty()
                && this->mWordList[0]->str == this->mSearchBar.getInputText()) {
                this->mScrollList.setWord(this->mWordList[0]);
            }
        }
        if (this->mWordList.size() > Core::RESULT_LIMIT)
            this->mWordList.resize(Core::RESULT_LIMIT);
        this->mScrollList.resetPosition();
    });

    // Scroll list
    mScrollList.setRect({341, 163, 641, 477});

    // Mode button
    mIsDefinitionSearch = false;
    mModeButton.setRect({688, 20, 309, 47});
    mModeButton.setTexture(
        TextureHolder::getInstance().get(TextureID::DefinitionSwitch));
    mModeButton.setColor(BLANK);
    mModeButton.setCallback([this]() {
        if (this->mIsDefinitionSearch) {
            this->mModeButton.setTexture(
                TextureHolder::getInstance().get(TextureID::DefinitionSwitch));
            this->mIsDefinitionSearch = false;
        } else {
            this->mModeButton.setTexture(
                TextureHolder::getInstance().get(TextureID::KeywordSwitch));
            this->mIsDefinitionSearch = true;
        }
    });

    mWordList = Dictionary::getInstance().getDict().searchKeyword("a b");
}

SearchState::~SearchState() {
}

bool SearchState::update(float dt) {
    mScrollList.update(dt);
    mSearchBar.update(dt);

    if (mSearchBar.getInputText() == "") {
        mSearchButton.setText("Random");
        mWordList = Dictionary::getInstance().getDict().getHistory();
    } else {
        mSearchButton.setText("Search");
        if (!mIsDefinitionSearch) {
            mWordList = Dictionary::getInstance().getDict().searchKeyword(
                mSearchBar.getInputText());
            if (mWordList.size() > Core::RESULT_LIMIT)
                mWordList.resize(Core::RESULT_LIMIT);
        }
    }

    mSearchButton.update(dt);
    mModeButton.update(dt);
    mNavBar.update(dt);

    return true;
}

void SearchState::draw() {
    ClearBackground(AppColor::BACKGROUND_1);
    mScrollList.draw();
    mSearchBar.draw();

    if (mSearchBar.getInputText() == "") {
        TextBox suggestionText("Don't know what to search?", {837, 76, 200, 1});
        suggestionText.setBorderThickness(0);
        suggestionText.setColor(BLANK);
        suggestionText.setTextSize(15);
        suggestionText.draw();
    }

    mSearchButton.draw();
    mModeButton.draw();
    mNavBar.draw();
    DrawLineEx({341, 163}, {982, 163}, 1, AppColor::TEXT);
}
