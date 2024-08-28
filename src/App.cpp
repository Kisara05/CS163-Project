#include <iostream>
#include "App.h"
#include "raylib.h"

App::App() {

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
    stateStack.draw();
    EndDrawing();
}