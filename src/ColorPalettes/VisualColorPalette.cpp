#include "VisualColorPalette.h"

#include <algorithm>
#include <cassert>

using namespace std;

const Color VisualColor::OPTIONS[] = {
    Color({87, 205, 230, 255}), Color({251, 188, 4, 255}),
    Color({238, 103, 92, 255}), Color({52, 168, 83, 255})};
// const Color VisualColor::OPTIONS[] = {
//     Color({244, 113, 162, 255}), Color({255, 213, 16, 255}),
//     Color({242, 52, 52, 255}), Color({16, 134, 255, 255})};

Color VisualColor::mColors[] = {
    VisualColor::OPTIONS[0], VisualColor::OPTIONS[1], VisualColor::OPTIONS[2],
    VisualColor::OPTIONS[3]};

Color VisualColor::getPrimaryColor() {
    return mColors[0];
}

Color VisualColor::getSecondaryColor() {
    return mColors[1];
}

Color VisualColor::getTertiaryColor() {
    return mColors[2];
}

Color VisualColor::getReferenceColor() {
    return mColors[3];
}

void VisualColor::setPrimaryColor(ColorIndex id) {
    replaceColor(OPTIONS[id], 0);
}

void VisualColor::setSecondaryColor(ColorIndex id) {
    replaceColor(OPTIONS[id], 1);
}

void VisualColor::setTertiaryColor(ColorIndex id) {
    replaceColor(OPTIONS[id], 2);
}

void VisualColor::setReferenceColor(ColorIndex id) {
    replaceColor(OPTIONS[id], 3);
}

void VisualColor::replaceColor(Color src, int index) {
    for (int i = 0; i < OPTIONS_SIZE; i++) {
        if (ColorToInt(mColors[i]) == ColorToInt(src)) {
            swap(mColors[i], mColors[index]);
            return;
        }
    }
    assert(false);
}