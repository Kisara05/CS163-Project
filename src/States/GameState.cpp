#include "GameState.h"

GameState::GameState(StateStack& stack, Context context)
: State(stack, context) {
    mNavBar.setCurNav(NavBar::NavID::Game);

    mWordGameBtn.setRect({420, 266, 241, 195});
    mWordGameBtn.setTexture(
        TextureHolder::getInstance().get(TextureID::WordGame));
    mWordGameBtn.setColor(BLANK);
    mWordGameBtn.setCallback([this]() {
        this->requestStackPop();
        this->requestStackPush(StateIDs::WordGame);
    });

    mDefinitionGameBtn.setRect({661, 266, 241, 195});
    mDefinitionGameBtn.setTexture(
        TextureHolder::getInstance().get(TextureID::DefinitionGame));
    mDefinitionGameBtn.setColor(BLANK);
    mDefinitionGameBtn.setCallback([this]() {
        this->requestStackPop();
        this->requestStackPush(StateIDs::DefinitionGame);
    });
}

GameState::~GameState() {
}

bool GameState::update(float dt) {
    mWordGameBtn.update(dt);
    mDefinitionGameBtn.update(dt);
    mNavBar.update(dt);
    return true;
}

void GameState::draw() {
    ClearBackground(AppColor::BACKGROUND_1);
    TextBox titleText("Let's play a game, shall we?", {371, 118, 700, 1});
    titleText.setBorderThickness(0);
    titleText.setColor(BLANK);
    titleText.setTextSize(52);
    titleText.draw();

    TextBox subtitleText("Choose your game", {535, 197, 300, 1});
    subtitleText.setBorderThickness(0);
    subtitleText.setColor(BLANK);
    subtitleText.setTextSize(32);
    subtitleText.draw();

    mWordGameBtn.draw();
    mDefinitionGameBtn.draw();

    DrawLineEx({661, 285}, {661, 443}, 1, AppColor::TEXT);

    mNavBar.draw();
}
