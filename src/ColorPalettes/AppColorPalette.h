#ifndef APP_COLORPALETTE_H
#define APP_COLORPALETTE_H
#include "raylib.h"
namespace AppColor {
    const Color BACKGROUND_1 = GetColor(0xFFFFFFFF);
    const Color BACKGROUND_2 = GetColor(0xDEF1FFFF);
    const Color BACKGROUND_OPAQUE = GetColor(0x000000BA);

    const Color TEXT = GetColor(0x000000FF);
    const Color TEXT_FADED = GetColor(0x818181FF);
    const Color TEXT_CONTRAST = GetColor(0xFFFFFFFF);

    const Color PRIMARY = GetColor(0x0C8CE9FF);

    const Color QUIZ_INCORRECT = GetColor(0xFF0000FF);
    const Color QUIZ_CORRECT = GetColor(0x309600FF);

}
#endif // APP_COLORPALETTE_H