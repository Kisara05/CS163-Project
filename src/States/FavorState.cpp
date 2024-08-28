#include "FavoriteState.h"

FavoriteState::FavoriteState(StateStack& stack, Context context)
: State(stack, context)
, mScrollList(mWordList) {
    mNavBar.setCurNav(NavBar::NavID::Favorite);

    // Scroll list
    mScrollList.setRect({341, 163, 641, 477});

    mWordList = Dictionary::getInstance().getDict().getFavoriteList();
}

FavoriteState::~FavoriteState() {
}

bool FavoriteState::update(float dt) {
    mScrollList.update(dt);

    mWordList = Dictionary::getInstance().getDict().getFavoriteList();

    mNavBar.update(dt);
    return true;
}

void FavoriteState::draw() {
    ClearBackground(AppColor::BACKGROUND_1);

    TextBox titleText("Favorite", {321, 63, 300, 1});
    titleText.setBorderThickness(0);
    titleText.setColor(BLANK);
    titleText.setTextSize(60);
    titleText.draw();

    mScrollList.draw();
    mNavBar.draw();
    DrawLineEx({341, 163}, {982, 163}, 1, AppColor::TEXT);
}
