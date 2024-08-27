#include "NavBar.h"

#include <cassert>
#include <iostream>

NavBar::NavBar() {
    mRect = {0, 0, 299, 640};
    mColor = AppColor::BACKGROUND_2;

    mDatasetSwitch.setRect({23, 19, 252, 67});
    mDatasetSwitch.setBorderThickness(0);
    mDatasetSwitch.setColor(BLANK);
    mDatasetSwitch.setTexture(
        TextureHolder::getInstance().get(TextureID::DatasetSwitch));
    mDatasetSwitch.setCallback([this]() {
        this->mDatasetSelectorHidden ^= 1;
    });

    for (int i = 0; i < 5; i++) {
        Button button;
        button.setCornerRoundness(0);
        button.setBorderThickness(0);
        button.setText(Dictionary::CORE[i].getDataName());
        button.setRect({26, (float)96 + i * 61, 246, 61});
        button.setColor(AppColor::BACKGROUND_1);
        button.setContentColor(AppColor::TEXT);
        button.setCallback([this, i]() {
            Dictionary::getInstance().setDict(i);
            this->mDatasetSelectorHidden = true;
        });
        mDatasetOptions.push_back(std::move(button));
    }

    mSettingsBtn.setRect({239, 580, 39, 39});
    mSettingsBtn.setColor(BLANK);
    mSettingsBtn.setTexture(
        TextureHolder::getInstance().get(TextureID::Settings));

    mOptionPanel = TextureHolder::getInstance().get(TextureID::OptionPanel);
    scaleTexture(mOptionPanel, {252, 341});
}

void NavBar::update(float dt) {
    mDatasetSwitch.update(dt);
    for (auto& p : mNavButtons) {
        if (mDatasetSelectorHidden)
            p.second.update(dt);
    }
    if (!mDatasetSelectorHidden) {
        for (auto& button : mDatasetOptions) {
            button.update(dt);
        }
    }
    mSettingsBtn.update(dt);
}

void NavBar::draw() {
    DrawRectangleRec(mRect, mColor);
    mDatasetSwitch.draw();
    TextBox dataName(Dictionary::getInstance().getDict().getDataName(),
                     {58, 25, 200, 61});
    dataName.setColor(BLANK);
    dataName.setBorderColor(BLANK);
    dataName.setTextSize(31);
    dataName.draw();
    for (auto& p : mNavButtons) {
        p.second.draw();
        if (p.first == mSelection) {
            Rectangle rect = p.second.getRect();
            DrawRectangleRec(rect, GetColor(0x00000011));
            DrawLineEx({0, rect.y}, {0, rect.y + rect.height}, 8,
                       AppColor::PRIMARY); // Indicator
        }
    }
    if (!mDatasetSelectorHidden) {
        DrawTexture(mOptionPanel, 23, 81, WHITE);
        // DrawRectangleRounded(
        //     {26, 81, 246, (float)30 + 61 * mDatasetOptions.size()}, 0.122,
        //     GUIComponent::ROUNDED_SEGMENTS, AppColor::BACKGROUND_1);
        for (auto& button : mDatasetOptions) {
            button.draw();
        }
    }
    mSettingsBtn.draw();
}

void NavBar::addNav(NavID id, std::function<void()> navigate) {
    Button navButton;
    const int BUTTON_HEIGHT = 56;
    navButton.setPosition(
        (Vector2){0, 112 + (float)BUTTON_HEIGHT * mNavButtons.size()});
    navButton.setSize({getSize().x, BUTTON_HEIGHT});
    navButton.setCornerRoundness(0);

    TextureID buttonTextureID;
    switch (id) {
        case NavID::Search:
            buttonTextureID = TextureID::SearchNav;
            break;
        case NavID::Favorite:
            buttonTextureID = TextureID::FavoriteNav;
            break;
        case NavID::Game:
            buttonTextureID = TextureID::GameNav;
            break;
    }
    navButton.setTexture(TextureHolder::getInstance().get(buttonTextureID));

    navButton.setColor(AppColor::BACKGROUND_2);
    // navButton.setContentColor(AppColor::TEXT);
    navButton.setCallback(navigate);
    mNavButtons[id] = std::move(navButton);
}

void NavBar::addSettingsNav(std::function<void()> navigate) {
    mSettingsBtn.setCallback(navigate);
}

void NavBar::setCurNav(NavID id) {
    auto found = mNavButtons.find(id);
    assert(found != mNavButtons.end());

    mSelection = id;
}
