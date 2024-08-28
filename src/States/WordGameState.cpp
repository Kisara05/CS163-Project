#include "WordGameState.h"

WordGameState::WordGameState(StateStack& stack, Context context)
: State(stack, context) {
    mNavBar.setCurNav(NavBar::NavID::Game);

    mQuiz = Dictionary::getInstance().getDict().getWordQuiz();
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
        this->mInfoPage.setWord(this->mQuiz.first);
    });

    mInfoPage.setRect({341, 163, 641, 477});
}

WordGameState::~WordGameState() {
}

bool WordGameState::update(float dt) {
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

void WordGameState::draw() {
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
        TextBox subtitleText("Guess the word:", {320, 28, 617, 1});
        subtitleText.setTextSize(35);
        subtitleText.setBorderColor(BLANK);
        subtitleText.setColor(BLANK);
        subtitleText.draw();

        TextBox wordText(mQuiz.first->orgStr, {331, 64, 498, 84});
        wordText.setTextSize(75);
        wordText.setBorderColor(BLANK);
        wordText.setColor(BLANK);
        wordText.makeShort();
        wordText.draw();

        if (mSelection) {
            mDetailsBtn.draw();
        }
        for (int i = 0; i < 4; i++) {
            mChoices[i].draw();
            TextBox defText(mQuiz.second[i + 1]->orgStr, mChoices[i].getRect());
            defText.setTextSize(20);
            defText.setColor(BLANK);
            defText.setBorderColor(BLANK);
            defText.draw();
        }
        mNextBtn.draw();
    }
    mNavBar.draw();
}

void WordGameState::generateNewQuiz() {
    mQuiz = Dictionary::getInstance().getDict().getWordQuiz();
    mSelection = nullptr;
    for (int i = 0; i < 4; i++) {
        mChoices[i].activate();
        mChoices[i].setBorderColor(AppColor::TEXT);
        mChoices[i].setBorderThickness(2);
    }
}