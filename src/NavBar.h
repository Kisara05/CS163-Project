#ifndef NAVBAR_H
#define NAVBAR_H

#include "Core/Dictionary.h"
#include "GUIComponents/Button.h"
#include "GUIComponents/GUIComponent.h"
#include "GUIComponents/TextBox.h"
#include "GUIComponents/GUIComponentHelper.h"

#include "raylib.h"

#include <functional>
#include <map>
#include <string>

class NavBar : public GUIComponent {
public:
    enum class NavID {
        None,
        Search,
        Favorite,
        Game
    };

public:
    NavBar();

    void update(float dt);
    void draw();

    void addNav(NavID id, std::function<void()> navigate);
    void addSettingsNav(std::function<void()> navigate);
    void setCurNav(NavID id);

private:
    Button mDatasetSwitch;
    std::map<NavID, Button> mNavButtons;
    NavID mSelection{NavID::None};

    bool mDatasetSelectorHidden{true};
    std::vector<Button> mDatasetOptions;

    Button mSettingsBtn;

    Texture2D mOptionPanel;
};

#endif // NAVBAR_H
