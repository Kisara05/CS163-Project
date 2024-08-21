#ifndef VISUAL_COLOR_H
#define VISUAL_COLOR_H

#include "raylib.h"

class VisualColor {
public:
    enum ColorIndex {
        Blue,
        Yellow,
        Red,
        Green,
    };
    static const int OPTIONS_SIZE = 4;
    static const Color OPTIONS[];

    static Color getPrimaryColor();
    static Color getSecondaryColor();
    static Color getTertiaryColor();
    static Color getReferenceColor();

    static void setPrimaryColor(ColorIndex id);
    static void setSecondaryColor(ColorIndex id);
    static void setTertiaryColor(ColorIndex id);
    static void setReferenceColor(ColorIndex id);

private:
    static Color mColors[OPTIONS_SIZE];
    static void replaceColor(Color src, int index);
};

#endif // VISUAL_COLOR_H