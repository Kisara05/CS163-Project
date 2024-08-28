#include "StateStack.h"
#include <cassert>

StateStack::StateStack(State::Context context)
: mContext(context) {
}

void StateStack::draw() {
    for (auto &state : mStack) {
        state->draw();
    }
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