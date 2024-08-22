#include "GUIComponent.h"

GUIComponent::GUIComponent() {
}

GUIComponent::~GUIComponent() {
}

void GUIComponent::update(float dt) {
}

Rectangle GUIComponent::getRect() const {
    return mRect;
}

void GUIComponent::setRect(Rectangle rect) {
    mRect = rect;
}

Vector2 GUIComponent::getPosition() const {
    return {mRect.x, mRect.y};
}

void GUIComponent::setPosition(Vector2 position) {
    mRect.x = position.x;
    mRect.y = position.y;
}

Vector2 GUIComponent::getSize() const {
    return {mRect.width, mRect.height};
}

void GUIComponent::setSize(Vector2 size) {
    mRect.width = size.x;
    mRect.height = size.y;
}

void GUIComponent::setColor(Color color) {
    mColor = color;
}

void GUIComponent::setBorderThickness(int thickness) {
    mBorderThickness = thickness;
}

void GUIComponent::setBorderColor(Color color) {
    mBorderColor = color;
}
