#ifndef STATES_SETTINGSSTATE_H
#define STATES_SETTINGSSTATE_H

#include "../Core/Dictionary.h"
#include "../GUIComponents/TextBox.h"
#include "../GUIComponents/InputBox.h"
#include "../GUIComponents/Button.h"
#include "../WordInfo.h"
#include "State.h"

#include <map>

class SettingsState : public State {
public:
    SettingsState(StateStack& stack, Context context);
    ~SettingsState();

    bool update(float dt);
    void draw();

private:
    Button mAddWordBtn;
    bool mIsOpenAddWord;
    InputBox mAddWordInputter;
    Button mConfirmAddWordBtn;

    float mErrorTimer{0};
    std::string mErrorString;

    Button mResetBtn;
    bool mIsOpenReset;
    Button mConfirmReset;

    WordInfo mInfoPage;
};

#endif // STATES_SETTINGSSTATE_H
