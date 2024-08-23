#ifndef BUTTON_H
#define BUTTON_H
#include "GUIComponent.h"
#include "raylib.h"
#include <functional>
#include <memory>
#include <string>

class Button : public GUIComponent {
public:
    typedef std::shared_ptr<Button> SmartPointer;

    typedef std::function<Color(Color)> Filter;

    typedef std::function<void()> Callback;

    enum class ButtonState {
        None,
        Focused,
        Active
    };

    explicit Button(Rectangle bounds = {0, 0, 0, 0});
    ~Button();
    void update(float dt);
    void draw();

    void setSize(Vector2 size);

    void setCallback(Callback callback);
    void triggerCallback();

    void setContentColor(Color color);

    void setText(const std::string text);
    void setTextSize(int size);
    void setTextBold(bool textBold);

    void setTexture(Texture2D texture);

    Color getColor() const;

    void setCornerRoundness(float cornerRoundness);

    void setInactivatedFilter(Filter filter);

    void activate();
    void deactivate();
private:
    void checkInteraction();
    
    ButtonState mState{ButtonState::None};

    Callback mCallback;

    Color mContentColor{WHITE};

    std::string mText;
    int mTextSize{0};
    bool mIsBold{false};

    bool mHasTexture{false};
    Texture2D mTexture;

    float mCornerRoundness{0.5};

    bool mIsActivated{true};
    Filter mInactivatedFilter;
};

#endif // BUTTON_H