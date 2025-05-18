#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <SDL3/SDL.h>

#include "box2d/math_functions.h"
#include "lib/box2d/src/body.h"


namespace donkeykong {

    struct Drawable {
        SDL_Texture* tex;
        SDL_FRect part;

        float scaleX;
        float scaleY;

        bool visible;
        bool flip= false;
    };

    struct Position {
        int x;
        int y;
    };

    struct Moveable {
        b2Vec2 velocity;
    };

    struct Body {
        b2BodyId body;
    };


}

#endif //COMPONENTS_H
