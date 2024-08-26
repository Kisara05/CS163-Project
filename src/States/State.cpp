#include "State.h"
#include "../StateStack.h"

State::State(StateStack &stack, Context context)
: mStack(&stack)
, mContext(context) {
    mNavBar.addNav(NavBar::NavID::Search, [this]() {
        this->requestStackPop();
        this->requestStackPush(StateIDs::Search);
    });
    mNavBar.addNav(NavBar::NavID::Favorite, [this]() {
        this->requestStackPop();
        this->requestStackPush(StateIDs::Favorite);
    });
    mNavBar.addNav(NavBar::NavID::Game, [this]() {
        this->requestStackPop();
        this->requestStackPush(StateIDs::Game);
    });
    mNavBar.addSettingsNav([this]() {
        this->requestStackPop();
        this->requestStackPush(StateIDs::Settings);
    });
}

State::~State() {
}

void State::requestStackPush(StateIDs stateID) {
    mStack->pushState(stateID);
}

void State::requestStackPop() {
    mStack->popState();
}

void State::requestStackClear() {
    mStack->clearStates();
}
