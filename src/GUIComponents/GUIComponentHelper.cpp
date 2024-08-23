#include "GUIComponentHelper.h"

Vector2 operator+ (const Vector2 &a, const Vector2 &b) {
    return {a.x + b.x, a.y + b.y};
}

Vector2 operator- (const Vector2 &a, const Vector2 &b) {
    return {a.x - b.x, a.y - b.y};
}

Vector2 operator* (const Vector2 &a, float x) {
    return {a.x * x, a.y * x};
}

Vector2 operator/ (const Vector2 &a, float x) {
    return {a.x / x, a.y / x};
}

void scaleTexture(Texture2D &src, Vector2 newSize) {
    Image img = LoadImageFromTexture(src);
    ImageResize(&img, newSize.x, newSize.y);
    src = LoadTextureFromImage(img);
}