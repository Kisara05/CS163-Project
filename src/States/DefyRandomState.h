#ifndef STATES_DEFINITIONGAMESTATE_H
#define STATES_DEFINITIONGAMESTATE_H

#include "../Core/Dictionary.h"
#include "../GUIComponents/Button.h"
#include "../GUIComponents/InputBox.h"
#include "../GUIComponents/TextBox.h"
#include "../WordList.h"
#include "State.h"

#include <map>

class DefinitionGameState : public State {
public:
    typedef std::pair<Core::Definition *, std::array<Core::Word *, 5>> Quiz;

public:
    DefinitionGameState(StateStack &stack, Context context);
    ~DefinitionGameState();

    bool update(float dt);
    void draw();

private:
    Quiz mQuiz;
    std::array<Button, 4> mChoices;
    Core::Word * mSelection{nullptr};

    Button mNextBtn;
    Button mDetailsBtn;

    WordInfo mInfoPage;

private:
    void generateNewQuiz();
};

#endif // STATES_DEFINITIONGAMESTATE_H
