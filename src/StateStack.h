#ifndef STATESTACK_H
#define STATESTACK_H
#include "StateStack.inl"

#include "States/State.h"

class StateStack {
public:
    explicit StateStack(State::Context context);
    bool isEmpty() const;

    void draw();

private:
    enum class Action {
        Push,
        Pop,
        Clear
    };

    struct PendingChange {
        explicit PendingChange(Action action,
            StateIDs stateID = StateIDs::None);

        Action action;
        StateIDs stateID;
    };

    void applyPendingChange();

    std::vector<State::Ptr> stack;
    std::vector<PendingChange> pendingList;

    std::map<StateIDs, std::function<State::Ptr()>> factories;
    State::Context context;
};
#endif