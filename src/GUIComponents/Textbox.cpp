#include "TextBox.h"

#include <iostream>

TextBox::TextBox(std::string defaultText, Rectangle bounds) {
    mRect = bounds;
    mColor = WHITE;
    mBorderColor = BLACK;
    mBorderThickness = 1;
    mText = defaultText;
    mActualHeight = bounds.height;
}

TextBox::~TextBox() {
}

void TextBox::update(float dt) {
}

void TextBox::draw() {
    if (mRect.width == 0)
        return;
    DrawRectangleRounded({mRect.x, mRect.y, mRect.width, mActualHeight},
                         mCornerRoundness, ROUNDED_SEGMENTS, mColor);
    if (mBorderThickness != 0)
        DrawRectangleRoundedLines(
            {mRect.x, mRect.y, mRect.width, mActualHeight}, mCornerRoundness,
            ROUNDED_SEGMENTS, mBorderThickness, mBorderColor);

    int textSize = mTextSize;
    if (textSize == 0) {
        textSize = std::min(16.0f, mRect.height * 2 / 3); // Default text size
    }
    Rectangle textArea = mRect;
    textArea.x += textSize / 3;
    textArea.y += textSize / 3;
    textArea.width -= 2 * textSize / 3;
    // textArea.height -= 2 * textSize / 3;

    std::vector<std::string> textLines;
    textLines.push_back("");

    std::istringstream iss(mText);
    do {
        std::string word;
        iss >> word;

        Vector2 tmpTextBounds = MeasureTextEx(
            FontHolder::getInstance().get(FontID::Inter, textSize),
            (textLines.back() + (textLines.back() == "" ? "" : " ") + word)
                .c_str(),
            textSize, 0);
        if (tmpTextBounds.x > textArea.width) {
            Vector2 wordBounds = MeasureTextEx(
                FontHolder::getInstance().get(FontID::Inter, textSize),
                word.c_str(), textSize, 0);
            while (MeasureTextEx(
                       FontHolder::getInstance().get(FontID::Inter, textSize),
                       word.c_str(), textSize, 0)
                       .x
                   > textArea.width) {
                int i = 0;
                while (i < word.size()
                       && MeasureTextEx(FontHolder::getInstance().get(
                                            FontID::Inter, textSize),
                                        word.substr(0, i).c_str(), textSize, 0)
                                  .x
                              <= textArea.width) {
                    i++;
                }
                if (textLines.back() == "") {
                    textLines.pop_back();
                }
                textLines.push_back(word.substr(0, i - 1));
                word.erase(0, i - 1);
            }
            if (textLines.back() == "") {
                textLines.pop_back();
            }
            textLines.push_back(word);
        } else {
            if (textLines.back() != "") {
                textLines.back() += " ";
            }
            textLines.back() += word;
        }
    } while (iss);

    if (mIsShort) {
        if (textLines.size()) {
            DrawTextEx(FontHolder::getInstance().get(FontID::Inter, textSize),
                       textLines[0].c_str(), {textArea.x, textArea.y}, textSize,
                       0, mTextColor);
        }
    } else {
        float yOffset = textArea.y;
        for (std::string line : textLines) {
            float startingX = textArea.x;
            DrawTextEx(FontHolder::getInstance().get(FontID::Inter, textSize),
                       line.c_str(), {startingX, yOffset}, textSize, 0,
                       mTextColor);
            yOffset += (float)textSize;
        }
        mActualHeight = std::max(mRect.height, yOffset - mRect.y + 2 * textSize / 3); // Update the height in draw function, kinda meh but i cant help
    }
}

void TextBox::setTextSize(int textSize) {
    mTextSize = textSize;
}

void TextBox::setCornerRoundness(float cornerRoundness) {
    mCornerRoundness = cornerRoundness;
}

void TextBox::setText(std::string text) {
    mText = text;
}

std::string TextBox::getText() const {
    return mText;
}

void TextBox::setTextColor(Color color) {
    mTextColor = color;
}

void TextBox::makeShort() {
    mIsShort = true;
}

float TextBox::getHeight() {
    return mActualHeight;
}

