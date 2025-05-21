#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <SDL3/SDL.h>

#include "box2d/math_functions.h"

#include <box2d/box2d.h>


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

    struct BarrelMove {
        bool isFalling = true; // true if the barrel is falling
        bool isFalled = false; // true if the barrel just touch the ground after falling
        float moveSpeed = 3.0f; // speed of the barrel
        int direction;
    };

    struct RespawnWhen{
        bool above = false;
        bool below = false;
        int when_y; // when y is above/below the respawn point

        int respawn_y; // y position of the respawn point
        int respawn_x; // x position of the respawn point
    };

    struct CollosionDetector {
        int entities = 0;
        float width =1.f;
        float height = 1.f;
    };

    struct Animation {

        enum class type {
            MARIO,
            BARREL,
            KONG,
            PRINCESS
        };

        Drawable** states_frames;
        int statesCount;
        int framesCount;

        int currentState = 0;
        int currentFrame = 0;
        type animType;
    };

    struct PrincessComponent {

    };


}

//TODO:
// 1. Collosion
// 2. Restart
// 3. Game over
// 4. Score
// 5. Hearts
// 6. Game over screen
// 7. Animations


#endif //COMPONENTS_H
