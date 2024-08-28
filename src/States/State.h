<<<<<<< HEAD
=======
#ifndef STATES_STATE_H
#define STATES_STATE_H

>>>>>>> 35a737ab971032c5e5ea341191577a0c7776152a
#include "../ColorPalettes/AppColorPalette.h"
#include "../ResourceHolders/TextureHolder.h"
#include "StateID.h"
#include "../NavBar.h"

#include "memory.h"

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
<<<<<<< HEAD
//#endif MEMORY.H
=======

#endif // STATES_STATE_H
>>>>>>> 35a737ab971032c5e5ea341191577a0c7776152a
