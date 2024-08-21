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
};

#endif // BUTTON_H