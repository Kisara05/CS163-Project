#include "memory.h"

class StateStack;

class State {
public:
	struct Context {};
    
private:
    StateStack* stack;
    Context context;
};
//#endif MEMORY.H