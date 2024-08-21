#include "StateStack.h"

StateStack::StateStack(State::Context Context)
	: context(Context) {
}

void StateStack::draw() {
    for (auto& state : stack) {
        state->draw();
    }
}

bool StateStack::isEmpty() const {
    return stack.empty();
}