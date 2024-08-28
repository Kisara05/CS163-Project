#ifndef STATES_STATE_H
#define STATES_STATE_H

#include "../ColorPalettes/AppColorPalette.h"
#include "../ResourceHolders/TextureHolder.h"
#include "StateID.h"
#include "../NavBar.h"

#include <memory>

class StateStack;

class State {
public:
    typedef std::unique_ptr<State> Ptr;

    struct Context {};

public:
    State(StateStack &stack, Context context);
    virtual ~State();

    virtual bool update(float dt) = 0;
    virtual void draw() = 0;

protected:
    NavBar mNavBar;

protected:
    void requestStackPush(StateIDs stateID);
    void requestStackPop();
    void requestStackClear();

private:
    StateStack *mStack;
    Context mContext;
};

#endif // STATES_STATE_H