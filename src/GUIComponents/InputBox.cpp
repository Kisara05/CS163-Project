#include "InputBox.h"

#include <iostream>

InputBox::InputBox(std::string defaultText, Rectangle bounds) {
    mRect = bounds;
    mColor = WHITE;
    mBorderColor = BLACK;
    mBorderThickness = 1;
    mInputText = defaultText;
    mIndexPos = defaultText.size();
    mInitHeight = bounds.height;
}

InputBox::~InputBox() {
}

void InputBox::setRect(Rectangle rect) {
    mRect.x = rect.x;
    mRect.y = rect.y;
    mRect.width = rect.width;
    if (mIsWrapped) {
        mInitHeight = rect.height;
    } else {
        mRect.height = rect.height;
    }
}

void InputBox::reset() {
    mInputText = "";
}

void InputBox::update(float dt) {
    checkInteraction();

    if (mIsFocused) {
        int key = GetCharPressed();
        while (key > 0) {
            mInputText.insert(mInputText.begin() + mIndexPos, key);
            mIndexPos++;
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && mIndexPos > 0) {
            mInputText.erase(mInputText.begin() + mIndexPos - 1);
            mIndexPos--;
        }
        if (IsKeyPressed(KEY_RIGHT) && mIndexPos < mInputText.size()) {
            mIndexPos++;
        }
        if (IsKeyPressed(KEY_LEFT) && mIndexPos > 0) {
            mIndexPos--;
        }
    }

    mCursorTick += dt;
    if (mCursorTick > 2 * CURSOR_TICK_COUNT) {
        mCursorTick -= 2 * CURSOR_TICK_COUNT;
    }
}

void InputBox::draw() {
    if (mRect.width == 0)
        return;

    DrawRectangleRounded(mRect, mCornerRoundness, ROUNDED_SEGMENTS, mColor);
    if (mBorderThickness != 0) {
        DrawRectangleRoundedLines(mRect, mCornerRoundness, ROUNDED_SEGMENTS,
                                  mBorderThickness, mBorderColor);
    }
    if (mIsWrapped) {
        drawTextWrapped();
    } else {
        drawTextOverflow();
    }
}

void InputBox::setOverflow() {
    mIsWrapped = false;
}

void InputBox::setWrapped() {
    mIsWrapped = true;
}

void InputBox::setTextSize(int textSize) {
    mTextSize = textSize;
}

void InputBox::setCornerRoundness(float cornerRoundness) {
    mCornerRoundness = cornerRoundness;
}

void InputBox::setPlaceHolder(const std::string& text) {
    mPlaceHolder = text;
}

std::string InputBox::getInputText() const {
    return mInputText;
}

float InputBox::getHeight() {
    return mRect.height;
}

void InputBox::activateClickability() {
    mClickable = true;
}

void InputBox::deactivateClickability() {
    mClickable = false;
}

std::function<bool(std::string)> InputBox::integerValidator(int min, int max) {
    return [min, max](std::string str) -> bool {
        if (!std::regex_match(str, std::regex("[0-9]+"))) {
            return false;
        }
        int num = std::stoi(str);
        return (min <= num && num <= max);
    };
}

std::function<bool(std::string)>
InputBox::integerSpaceSeparatedListValidator() {
    return [](std::string str) -> bool {
        return std::regex_match(str,
                                std::regex("(?:-?\\d+)?(?:\\s+-?\\d+)*\\s*"));
    };
}

void InputBox::checkInteraction() {
    Vector2 mousePoint = GetMousePosition();

    if (mClickable && CheckCollisionPointRec(mousePoint, mRect)) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        mIsMouseHovered = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mIsFocused = true;
        }
    } else {
        if (mIsMouseHovered) {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
        mIsMouseHovered = false;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mIsFocused = false;
        }
    }
}

void InputBox::drawTextOverflow() {
    int textSize = mTextSize;
    if (mTextSize == 0) {
        textSize = mRect.height * 2 / 3;
    }
    std::string displayText = mInputText;
    if (mInputText == "") {
        displayText = mPlaceHolder;
    }
    Vector2 textBounds =
        MeasureTextEx(FontHolder::getInstance().get(FontID::Inter, textSize),
                      displayText.c_str(), textSize, 0);

    BeginScissorMode(mRect.x + textSize / 3, mRect.y,
                     mRect.width - textSize / 3, mRect.height);

    float startingX = mRect.x + textSize / 3;
    float startingY = mRect.y + textSize / 3;

    Color mDisplayColor = mTextColor;
    if (mInputText == "") {
        mDisplayColor = Fade(mDisplayColor, 0.2);
    }

    DrawTextEx(FontHolder::getInstance().get(FontID::Inter, textSize),
               displayText.c_str(), {startingX, startingY}, textSize, 0,
               mDisplayColor);
    if (mIsFocused)
        drawCursorIndicator(
            startingX
                + MeasureTextEx(
                      FontHolder::getInstance().get(FontID::Inter, textSize),
                      mInputText.substr(0, mIndexPos).c_str(), textSize, 0)
                      .x,
            startingY, startingY + textBounds.y);
    EndScissorMode();
}

void InputBox::drawTextWrapped() {
    int textSize = mTextSize;
    if (textSize == 0) {
        textSize = std::min(16.0f, mInitHeight * 2 / 3); // Default text size
    }
    Rectangle textArea = mRect;
    textArea.x += mTextSize / 3;
    textArea.y += mTextSize / 3;
    textArea.width -= 2 * mTextSize / 3;
    textArea.height -= 2 * mTextSize / 3;

    std::vector<std::string> textLines;
    textLines.push_back("");

    std::istringstream iss(mInputText);
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

    float yOffset = textArea.y;
    for (std::string line : textLines) {
        float startingX = textArea.x;
        DrawTextEx(FontHolder::getInstance().get(FontID::Inter, textSize),
                   line.c_str(), {startingX, yOffset}, textSize, 0, mTextColor);
        yOffset += (float)textSize;
    }
    mRect.height =
        std::max(mInitHeight,
                 yOffset - mRect.y
                     + 2 * textSize / 3); // Update the height in draw function
}

void InputBox::drawCursorIndicator(float x, float y1, float y2) {
    if (mCursorTick < CURSOR_TICK_COUNT) {
        if (y1 > y2) {
            DrawLineEx({x, y1}, {x, y2}, (y1 - y2) * 0.05, mTextColor);
        }
        else if (y1 < y2) {
            DrawLineEx({x, y1}, {x, y2}, (y2 - y1) * 0.05, mTextColor);
        }
        else DrawLineEx({x, y1}, {x, y2}, 0, mTextColor);
    }
}
