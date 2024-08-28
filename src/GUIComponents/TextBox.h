#ifndef GUICOMPONENTS_TEXTBOX_H
#define GUICOMPONENTS_TEXTBOX_H

#include "GUIComponent.h"

#include "raylib.h"

#include <functional>
#include <memory>
#include <string>
#include <sstream>
#include <vector>

class TextBox : public GUIComponent {
public:
    static constexpr float CURSOR_TICK_COUNT = 0.5;

public:
    typedef std::shared_ptr<TextBox> Ptr;

public:
    explicit TextBox(std::string defaultText = "", Rectangle bounds = {0, 0, 0, 0});
    ~TextBox();

    void update(float dt);
    void draw();

    void setTextSize(int textSize);
    void setCornerRoundness(float cornerRoundness);

    void setText(std::string text);
    std::string getText() const;

    void setTextColor(Color color);

    void makeShort();

    float getHeight();

private:
    std::string mText;
    Color mTextColor{BLACK};
    int mTextSize{0};

    float mCornerRoundness{0.5};

    bool mIsShort{false};

    float mActualHeight;

};

#endif //GUICOMPONENTS_TEXTBOX_H