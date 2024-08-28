#ifndef STATES_SEARCHSTATE_H
#define STATES_SEARCHSTATE_H

#include "../Core/Dictionary.h"
#include "../GUIComponents/TextBox.h"
#include "../GUIComponents/InputBox.h"
#include "../GUIComponents/Button.h"
#include "../WordList.h"
#include "State.h"

#include <map>

class SearchState : public State {
public:
    SearchState(StateStack& stack, Context context);
    ~SearchState();

    bool update(float dt);
    void draw();

private:
    std::vector<Core::Word*> mWordList;

    bool mIsDefinitionSearch;

private: // UI elements
    InputBox mSearchBar;
    Button mSearchButton;
    WordList mScrollList;

    Button mModeButton;
};

#endif // STATES_SEARCHSTATE_H
