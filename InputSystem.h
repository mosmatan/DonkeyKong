#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <SDL3/SDL.h>
#include "bagel.h"
#include "Components.h"
#include <box2d/box2d.h>

using namespace bagel;

namespace donkeykong {


struct PlayerControl {
    bool canJump = false;
    bool isOnLadder = false;
    float jumpForce = 5.0f;
    float moveSpeed = 5.0f;
    float climbSpeed = 2.0f;
};

class InputSystem {
public:
    InputSystem() = default;

    void update(const Uint8* keyboardState) {
        for (ent_type e{0}; e.id <= World::maxId().id; ++e.id) {
            if (World::mask(e).test(mask)) {
                auto& body = World::getComponent<Body>(e);
                auto& control = World::getComponent<PlayerControl>(e);
                auto& drawable = World::getComponent<Drawable>(e);

                if (!b2Body_IsValid(body.body)) {
                    continue;
                }

                b2Vec2 velocity = b2Body_GetLinearVelocity(body.body);

                if (control.isOnLadder) {
                    //ladder climbing behavior
                    if (keyboardState[SDL_SCANCODE_UP] || keyboardState[SDL_SCANCODE_W]) {
                        velocity.y = -control.climbSpeed; // Climb up (negative Y is up)
                    }
                    else if (keyboardState[SDL_SCANCODE_DOWN] || keyboardState[SDL_SCANCODE_S]) {
                        velocity.y = control.climbSpeed; // Climb down
                    }
                    else {
                        velocity.y = 0; //if up/down not pressed, stop moving on ladder
                    }

                    // Allow limited horizontal movement on ladders
                    if (keyboardState[SDL_SCANCODE_LEFT] || keyboardState[SDL_SCANCODE_A]) {
                        velocity.x = -control.moveSpeed * 0.5f; //slower speed on ladder
                        drawable.flip = false;
                    }
                    else if (keyboardState[SDL_SCANCODE_RIGHT] || keyboardState[SDL_SCANCODE_D]) {
                        velocity.x = control.moveSpeed * 0.5f;
                        drawable.flip = true;
                    }
                    else {
                        velocity.x = 0; //no right/left velocity on ladder
                    }

                    //jump from ladder
                    if (keyboardState[SDL_SCANCODE_SPACE]) {
                        velocity.y = -control.jumpForce;
                        control.isOnLadder = false;
                    }
                }
                else {
                    //normal movement behavior (not on ladder)
                    //left/right movement
                    if (keyboardState[SDL_SCANCODE_LEFT] || keyboardState[SDL_SCANCODE_A]) {
                        velocity.x = -control.moveSpeed;
                        drawable.flip = false;
                    }
                    else if (keyboardState[SDL_SCANCODE_RIGHT] || keyboardState[SDL_SCANCODE_D]) {
                        velocity.x = control.moveSpeed;
                        drawable.flip = true;
                    }
                    else {
                        velocity.x *= 0.8f;
                    }

                    //jump
                    if ((keyboardState[SDL_SCANCODE_UP] || keyboardState[SDL_SCANCODE_W] ||
                         keyboardState[SDL_SCANCODE_SPACE]) && control.canJump) {
                        velocity.y = -control.jumpForce; // Negative Y is up
                        control.canJump = false; // Can't jump again until grounded
                    }
                }
                b2Body_SetLinearVelocity(body.body, velocity);
            }
        }
    }

private:
    static inline Mask mask = MaskBuilder()
        .set<Body>()
        .set<PlayerControl>()
        .set<Drawable>()
        .build();
};

} // donkeykong

#endif //INPUTSYSTEM_H