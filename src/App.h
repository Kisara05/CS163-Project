#ifndef APP_H
#define APP_H
#include "ResourceHolders/FontHolder.h"
#include "ResourceHolders/TextureHolder.h"
#include "StateStack.h"

class App {
public:
    static constexpr float WINDOW_WIDTH = 1024;
    static constexpr float WINDOW_HEIGHT = 640;
    static constexpr char* WINDOW_TITLE = "CS163 - Dictionary App";

    static constexpr int FPS = 30;

public:
    App();
    ~App();

    void initApp();
    void renderApp();
    void update(float dt);

    void registerStates();

    void loadTextures();
    void loadFonts();

private:
    StateStack mStateStack;
};

#endif