#include "DefinitionGameState.h"

DefinitionGameState::DefinitionGameState(StateStack& stack, Context context)
: State(stack, context) {
    mNavBar.setCurNav(NavBar::NavID::Game);

    mQuiz = Dictionary::getInstance().getDict().getDefinitionQuiz();
    for (int i = 0; i < 4; i++) {
        mChoices[i] = Button((Rectangle){331, (float)224 + 85 * i, 661, 75});
        mChoices[i].setColor(AppColor::BACKGROUND_1);
        mChoices[i].setBorderThickness(2);
        mChoices[i].setBorderColor(AppColor::TEXT);
        mChoices[i].setCornerRoundness(20.0 * 2 / 75);
        mChoices[i].setInactivatedFilter([](Color color) {
            return color; // do nothing
        });
        mChoices[i].setCallback([this, i]() {
            this->mSelection = this->mQuiz.second[i + 1];
            this->mChoices[i].setBorderThickness(4);
            this->mChoices[i].setBorderColor(
                AppColor::QUIZ_INCORRECT); // Set it to incorrect first, then
                                           // correct it later

            for (int j = 0; j < 4; j++) {
                this->mChoices[j].deactivate();
            }
        });
    }

    mNextBtn.setRect({869, 576, 123, 40});
    mNextBtn.setCornerRoundness(12.0 * 2 / 40);
    mNextBtn.setColor(AppColor::PRIMARY);
    mNextBtn.setContentColor(AppColor::TEXT_CONTRAST);
    mNextBtn.setText("Next");
    mNextBtn.setCallback([this]() {
        this->generateNewQuiz();
    });

    mDetailsBtn.setRect({812, 20, 185, 47});
    mDetailsBtn.setTexture(
        TextureHolder::getInstance().get(TextureID::Details));
    mDetailsBtn.setColor(BLANK);
    mDetailsBtn.setCornerRoundness(13.0 * 2 / 47);
    mDetailsBtn.setBorderThickness(1);
    mDetailsBtn.setBorderColor(AppColor::TEXT);
    mDetailsBtn.setCallback([this]() {
        this->mInfoPage.setWord(this->mQuiz.second[0]);
    });

    mInfoPage.setRect({341, 163, 641, 477});
}

DefinitionGameState::~DefinitionGameState() {
}

bool DefinitionGameState::update(float dt) {
    if (mInfoPage.isActivated()) {
        mInfoPage.update(dt);
    } else {
        for (int i = 0; i < 4; i++) {
            mChoices[i].update(dt);
        }

        if (mSelection) {
            mDetailsBtn.update(dt);
            for (int i = 0; i < 4; i++) {
                if (mQuiz.second[0] == mQuiz.second[i + 1]) {
                    mChoices[i].setBorderThickness(4);
                    mChoices[i].setBorderColor(AppColor::QUIZ_CORRECT);
                }
            }
        }

        mNextBtn.update(dt);
    }
    mNavBar.update(dt);
    return true;
}

void DefinitionGameState::draw() {
    ClearBackground(AppColor::BACKGROUND_1);
    if (mInfoPage.isActivated()) {
        TextBox titleText("Let's review!", {321, 63, 600, 1});
        titleText.setBorderThickness(0);
        titleText.setColor(BLANK);
        titleText.setTextSize(60);
        titleText.draw();

        mInfoPage.draw();

        DrawLineEx({341, 163}, {982, 163}, 1, AppColor::TEXT);
    } else {
        TextBox subtitleText("Guess the definition:", {320, 28, 617, 1});
        subtitleText.setTextSize(35);
        subtitleText.setBorderColor(BLANK);
        subtitleText.setColor(BLANK);
        subtitleText.draw();

        TextBox defText(mQuiz.first->orgStr, {346, 96, 606, 1});
        defText.setTextSize(25);
        defText.setBorderColor(BLANK);
        defText.setColor(BLANK);
        defText.draw();

        if (mSelection) {
            mDetailsBtn.draw();
        }
        for (int i = 0; i < 4; i++) {
            mChoices[i].draw();
            TextBox wordText(mQuiz.second[i + 1]->orgStr,
                             mChoices[i].getRect());
            wordText.setTextSize(40);
            wordText.setColor(BLANK);
            wordText.setBorderColor(BLANK);
            wordText.makeShort();
            wordText.draw();
        }
        mNextBtn.draw();
    }
    mNavBar.draw();
}

void DefinitionGameState::generateNewQuiz() {
    mQuiz = Dictionary::getInstance().getDict().getDefinitionQuiz();
    mSelection = nullptr;
    for (int i = 0; i < 4; i++) {
        mChoices[i].activate();
        mChoices[i].setBorderColor(AppColor::TEXT);
        mChoices[i].setBorderThickness(2);
    }
}