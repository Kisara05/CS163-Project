#include "SettingsState.h"

SettingsState::SettingsState(StateStack& stack, Context context)
: State(stack, context) {
    mInfoPage.setRect({341, 163, 641, 477});

    // Add word settings
    mIsOpenAddWord = false;
    mAddWordBtn.setColor(BLANK);
    mAddWordBtn.setCallback([this]() {
        this->mIsOpenAddWord ^= 1;
    });

    mAddWordInputter.setCornerRoundness(1);
    mAddWordInputter.setColor(AppColor::BACKGROUND_1);
    mAddWordInputter.setBorderThickness(1);
    mAddWordInputter.setBorderColor(AppColor::TEXT);
    mAddWordInputter.setPlaceHolder("Enter a word...");

    mConfirmAddWordBtn.setText("Add");
    mConfirmAddWordBtn.setTextSize(24);
    mConfirmAddWordBtn.setContentColor(AppColor::TEXT_CONTRAST);
    mConfirmAddWordBtn.setColor(AppColor::PRIMARY);
    mConfirmAddWordBtn.setCornerRoundness(1);
    mConfirmAddWordBtn.setCallback([this]() {
        std::string input = this->mAddWordInputter.getInputText();
        if (input == "") {
            this->mErrorTimer = 4.0;
            this->mErrorString = "Please enter a word.";
            return;
        }
        Core::Word* word = Dictionary::getInstance().getDict().addWord(input);
        if (word == nullptr) {
            this->mErrorTimer = 4.0;
            this->mErrorString = "This word has already been added.";
            return;
        }
        this->mInfoPage.setWord(word);
    });

    // Reset settings
    mIsOpenReset = false;
    mResetBtn.setColor(BLANK);
    mResetBtn.setCallback([this]() {
        this->mIsOpenReset ^= 1;
    });

    mConfirmReset.setText("Confirm");
    mConfirmReset.setTextSize(24);
    mConfirmReset.setContentColor(AppColor::TEXT_CONTRAST);
    mConfirmReset.setColor(AppColor::PRIMARY);
    mConfirmReset.setCornerRoundness(1);
    mConfirmReset.setCallback([this]() {
        Dictionary::getInstance().getDict().resetDefault();
    });
}

SettingsState::~SettingsState() {
}

bool SettingsState::update(float dt) {
    if (!mInfoPage.isActivated()) {
        mAddWordBtn.setRect({367, 181, 591, 81});
        mAddWordBtn.setCornerRoundness((float)20 * 2 / 81);
        mAddWordBtn.update(dt);
        if (mIsOpenAddWord) {
            mAddWordInputter.setRect({396, 263, 409, 42});
            mConfirmAddWordBtn.setRect({836, 263, 106, 42});

            mAddWordInputter.update(dt);
            mConfirmAddWordBtn.update(dt);
        }
        mResetBtn.setRect(
            {367, (float)181 + (mIsOpenAddWord ? 139 : 81) + 18, 591, 81});
        mResetBtn.setCornerRoundness((float)20 * 2 / 81);
        mResetBtn.update(dt);
        if (mIsOpenReset) {
            mConfirmReset.setRect({800, mResetBtn.getRect().y + 82, 142, 42});

            mConfirmReset.update(dt);
        }
    }
    mInfoPage.update(dt);
    mNavBar.update(dt);
    return true;
}

void SettingsState::draw() {
    ClearBackground(AppColor::BACKGROUND_1);

    TextBox titleText("Settings", {321, 63, 300, 1});
    titleText.setBorderThickness(0);
    titleText.setColor(BLANK);
    titleText.setTextSize(60);
    titleText.draw();

    if (mIsOpenAddWord) {
        DrawRectangleRoundedLines({367, 181, 591, 139}, 20.0 * 2 / 139,
                                  GUIComponent::ROUNDED_SEGMENTS, 1,
                                  AppColor::TEXT);
        mAddWordBtn.draw();
        mAddWordInputter.draw();
        mConfirmAddWordBtn.draw();
    } else {
        DrawRectangleRoundedLines({367, 181, 591, 81}, 20.0 * 2 / 81,
                                  GUIComponent::ROUNDED_SEGMENTS, 1,
                                  AppColor::TEXT);
        mAddWordBtn.draw();
    }
    TextBox addWordText("Add a word", {384, 185, 205, 1});
    addWordText.setBorderThickness(0);
    addWordText.setColor(BLANK);
    addWordText.setTextSize(25);
    addWordText.draw();
    TextBox addWordSubtext(
        "Got a word that hasn't been in our dictionary? Add it now!",
        {387, 221, 412, 1});
    addWordSubtext.setBorderThickness(0);
    addWordSubtext.setColor(BLANK);
    addWordSubtext.setTextSize(17);
    addWordSubtext.setTextColor(AppColor::TEXT_FADED);
    addWordSubtext.draw();

    if (mIsOpenReset) {
        DrawRectangleRoundedLines(
            {367, mResetBtn.getRect().y, 591, 139}, 20.0 * 2 / 139,
            GUIComponent::ROUNDED_SEGMENTS, 1, AppColor::TEXT);
        mResetBtn.draw();
        mConfirmReset.draw();
    } else {
        DrawRectangleRoundedLines({367, mResetBtn.getRect().y, 591, 81},
                                  20.0 * 2 / 81, GUIComponent::ROUNDED_SEGMENTS,
                                  1, AppColor::TEXT);
        mResetBtn.draw();
    }
    TextBox resetText("Restore dictionary",
                      {384, mResetBtn.getRect().y + 4, 205, 1});
    resetText.setBorderThickness(0);
    resetText.setColor(BLANK);
    resetText.setTextSize(25);
    resetText.draw();
    TextBox resetSubtext(
        "Restore the current dictionary back to its original data.",
        {387, mResetBtn.getRect().y + 40, 412, 1});
    resetSubtext.setBorderThickness(0);
    resetSubtext.setColor(BLANK);
    resetSubtext.setTextSize(17);
    resetSubtext.setTextColor(AppColor::TEXT_FADED);
    resetSubtext.draw();

    mInfoPage.draw();
    mNavBar.draw();
    DrawLineEx({341, 163}, {982, 163}, 1, AppColor::TEXT);
}