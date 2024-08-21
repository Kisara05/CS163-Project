#ifndef STATESTACK_H
#define STATESTACK_H
#include "StateStack.inl"

#include "States/State.h"

class StateStack {
public:
    explicit StateStack(State::Context context);
    bool isEmpty() const;
   
    bool isEmpty() const;
};
#endif