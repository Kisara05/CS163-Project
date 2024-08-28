#ifndef STATES_FAVORITESTATE_H
#define STATES_FAVORITESTATE_H

#include "../Core/Dictionary.h"
#include "../GUIComponents/TextBox.h"
#include "../GUIComponents/InputBox.h"
#include "../GUIComponents/Button.h"
#include "../WordList.h"
#include "State.h"

#include <map>

class FavoriteState : public State {
public:
    FavoriteState(StateStack& stack, Context context);
    ~FavoriteState();

    bool update(float dt);
    void draw();

private:
    std::vector<Core::Word*> mWordList;

private: // UI elements
    WordList mScrollList;
};

#endif // STATES_FAVORITESTATE_H
