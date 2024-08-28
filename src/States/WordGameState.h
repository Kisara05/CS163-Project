#ifndef STATES_WORDGAMESTATE_H
#define STATES_WORDGAMESTATE_H

#include "../Core/Dictionary.h"
#include "../GUIComponents/Button.h"
#include "../GUIComponents/InputBox.h"
#include "../GUIComponents/TextBox.h"
#include "../WordList.h"
#include "State.h"

#include <map>

class WordGameState : public State {
public:
    typedef std::pair<Core::Word *, std::array<Core::Definition *, 5>> Quiz;

public:
    WordGameState(StateStack &stack, Context context);
    ~WordGameState();

    bool update(float dt);
    void draw();

private:
    Quiz mQuiz;
    std::array<Button, 4> mChoices;
    Core::Definition * mSelection{nullptr};

    Button mNextBtn;
    Button mDetailsBtn;

    WordInfo mInfoPage;

private:
    void generateNewQuiz();
};

#endif // STATES_WORDGAMESTATE_H
