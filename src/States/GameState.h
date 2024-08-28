#ifndef STATES_GAMESTATE_H
#define STATES_GAMESTATE_H

#include "../Core/Dictionary.h"
#include "../GUIComponents/Button.h"
#include "../GUIComponents/InputBox.h"
#include "../GUIComponents/TextBox.h"
#include "../WordList.h"
#include "State.h"

#include <map>

class GameState : public State {
public:
    GameState(StateStack& stack, Context context);
    ~GameState();

    bool update(float dt);
    void draw();

private:
    Button mWordGameBtn;
    Button mDefinitionGameBtn;
};

#endif // STATES_GAMESTATE_H
