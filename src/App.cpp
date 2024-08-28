#include <iostream>
#include "ResourceHolders/ResourceID.h"
#include "App.h"
#include "raylib.h"
#include "States/SearchState.h"
#include "States/FavorState.h"
#include "States/GameState.h"
#include "States/WordGameState.h"
#include "States/DefyGameState.h"
#include "States/SettingsState.h"
#include "States/StateID.h"

App::App() : mStateStack(State::Context()) {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(FPS);

    loadTextures();
    loadFonts();

    // SetWindowIcon(LoadImageFromTexture(
    //     TextureHolder::getInstance().get(TextureID::IconLogo)));

    registerStates();
    mStateStack.pushState(StateIDs::Search);
}

App::~App() {
    CloseWindow(); //Close app window
}

void App::initApp() {
    while (!WindowShouldClose()) {//check if KEY_ESCAPE or Exit button is pressed {
        update(GetFrameTime());
        renderApp();
    }
}

void App::renderApp() {
    BeginDrawing();
    mStateStack.draw();
    EndDrawing();
}