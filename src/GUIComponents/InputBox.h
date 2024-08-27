#ifndef GUICOMPONENTS_INPUTBOX_H
#define GUICOMPONENTS_INPUTBOX_H

#include "Button.h"
#include "GUIComponent.h"

#include "raylib.h"

#include <functional>
#include <memory>
#include <regex>
#include <string>

class InputBox : public GUIComponent {
public:
    static constexpr float CURSOR_TICK_COUNT = 0.5;

public:
    typedef std::shared_ptr<InputBox> Ptr;

public:
    explicit InputBox(std::string defaultText = "",
                      Rectangle bounds = {0, 0, 0, 0});
    ~InputBox();

    void setRect(Rectangle rect);

    void reset();

    void update(float dt);
    void draw();

    void setOverflow();
    void setWrapped();

    void setTextSize(int textSize);
    void setCornerRoundness(float cornerRoundness);

    void setPlaceHolder(const std::string &text);

    std::string getInputText() const;

    float getHeight();

    void activateClickability();
    void deactivateClickability();

public:
    static std::function<bool(std::string)> integerValidator(int min, int max);
    static std::function<bool(std::string)>
    integerSpaceSeparatedListValidator();

private:
    void checkInteraction();

    void drawTextOverflow();
    void drawTextWrapped();

    void drawCursorIndicator(float x, float y1, float y2);

private:
    std::string mInputText;
    Color mTextColor{BLACK};
    int mTextSize{0};

    std::string mPlaceHolder;

    bool mIsMouseHovered{false};
    bool mIsFocused{false};
    int mIndexPos{0};
    float mCursorTick{0};

    float mCornerRoundness{0.5};

    bool mIsWrapped{false};

    float mInitHeight;

    bool mClickable{true};
};

#endif // GUICOMPONENTS_INPUTBOX_H
