#ifndef GUICOMPONENTHELPER_H
#define GUICOMPONENTHELPER_H

#include "raylib.h"

Vector2 operator+ (const Vector2 &a, const Vector2 &b);

Vector2 operator- (const Vector2 &a, const Vector2 &b);

Vector2 operator* (const Vector2 &a, float x);

Vector2 operator/ (const Vector2 &a, float x);

void scaleTexture(Texture2D &src, Vector2 newSize);

#endif // GUICOMPONENTHELPER_H