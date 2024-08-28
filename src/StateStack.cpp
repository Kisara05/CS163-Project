#include "StateStack.h"
#include <cassert>

StateStack::StateStack(State::Context context)
: mContext(context) {
}

void StateStack::draw() {
    for (auto& state : stack) {
        state->draw();
    }
}

bool StateStack::isEmpty() const {
    return stack.empty();
}

StateStack::PendingChange::PendingChange(Action action, StateIDs stateID)
    : action(action)
    , stateID(stateID) {
}

void StateStack::applyPendingChange() {
    for (auto& changer : pendingList) {
        switch (changer.action) {
        case Action::Push:
            stack.push_back(createState(changer.stateID));
            break;

        case Action::Pop:
            stack.pop_back();
            break;

        case Action::Clear:
            stack.clear();
            break;
        }
    }
    pendingList.clear();
}