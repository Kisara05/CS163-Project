

#include "../ColorPalettes/AppColorPalette.h"
#include "../ResourceHolders/TextureHolder.h"
#include "StateID.h"
#include "../NavBar.h"

#include <memory.h>

class StateStack;

class State {
public:
    typedef std::unique_ptr<State> Ptr;
	struct Context {};
    State(StateStack &stack, Context context);
    virtual ~State();

    virtual bool update(float dt) = 0;
    virtual void draw() = 0;

protected:
    NavBar mNavBar;
    void requestStackPush(StateIDs stateID);
    void requestStackPop();
    void requestStackClear();

private:
    StateStack* mStack;
    Context mContext;
};