#include "StateStack.h"
#include <cassert>

StateStack::StateStack(State::Context context)
: mContext(context) {
}

void StateStack::update(float dt) {
    for (auto it = mStack.rbegin(); it != mStack.rend(); it++) {
        if ((*it)->update(dt) == false) {
            break;
        }
    }
    applyPendingChange();
}

void StateStack::draw() {
    for (auto &state : mStack) {
        state->draw();
    }
}

void StateStack::pushState(StateIDs stateID) {
    mPendingList.push_back(PendingChange(Action::Push, stateID));
}

void StateStack::popState() {
    mPendingList.push_back(PendingChange(Action::Pop));
}

void StateStack::clearStates() {
    mPendingList.push_back(PendingChange(Action::Clear));
}

bool StateStack::isEmpty() const {
    return mStack.empty();
}

StateStack::PendingChange::PendingChange(Action action, StateIDs stateID)
    : action(action)
    , stateID(stateID) {
}

void StateStack::applyPendingChange() {
    for (auto &change : mPendingList) {
        switch (change.action) {
            case Action::Push:
                mStack.push_back(createState(change.stateID));
                break;

            case Action::Pop:
                mStack.pop_back();
                break;

            case Action::Clear:
                mStack.clear();
                break;
        }
    }
    mPendingList.clear();
}

State::Ptr StateStack::createState(StateIDs stateID) {
    auto found = mFactories.find(stateID);
    assert(found != mFactories.end());

    return found->second();
}