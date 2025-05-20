//
// Created by Matan Moskovich on 19/05/2025.
//

#ifndef BARREL_H
#define BARREL_H
#include "bagel.h"
#include "Components.h"

using namespace bagel;

namespace donkeykong {

class BarrelEntity {

private:

    static constexpr float TEX_SCALE_WIDTH_BARREL = 1.6f;
    static constexpr float TEX_SCALE_HEIGHT_BARREL = 1.6f;
    static constexpr float BARREL_BODY_WIDTH = 14;
    static constexpr float BARREL_BODY_HEIGHT = 18;

    static inline Drawable** BARREL_ANIMATION = nullptr;

public:

    static Entity create(SDL_Texture* tex, int x, int y);
};

} // donkeykong

#endif //BARREL_H
