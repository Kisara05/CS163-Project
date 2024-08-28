#ifndef STATESTACK_H
#define STATESTACK_H

#include "StateStack.inl"

#include "States/State.h"
#include "States/StateID.h"

#include <functional>
#include <vector>
#include <map>

class StateStack {
public:
    explicit StateStack(State::Context context);
    template <typename StateType>

    void registerState(StateIDs stateID);

    void update(float dt);
    void draw();

    void pushState(StateIDs stateID);
    void popState();
    void clearStates();

    bool isEmpty() const;

    void draw();

private:
    enum class Action {
        Push,
        Pop,
        Clear
    };

    struct PendingChange {
        explicit PendingChange(Action action, StateIDs stateID = StateIDs::None);
        Action action;
        StateIDs stateID;
    };

    void applyPendingChange();
    State::Ptr createState(StateIDs stateID);

    std::vector<State::Ptr> stack;
    std::vector<PendingChange> pendingList;

    std::map<StateIDs, std::function<State::Ptr()>> factories;
    State::Context mContext;
};

#endif // STATESTACK_H