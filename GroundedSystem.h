#ifndef GROUNDEDSYSTEM_H
#define GROUNDEDSYSTEM_H

#include "bagel.h"
#include "Components.h"
#include "InputSystem.h"
#include <box2d/box2d.h>

using namespace bagel;

namespace donkeykong {

    class GroundedSystem {
    public:
        GroundedSystem() = default;

        //update if can jump
        void update() {
            for (ent_type e{0}; e.id <= World::maxId().id; ++e.id) {
                if (World::mask(e).test(mask)) {
                    auto& body = World::getComponent<Body>(e);
                    auto& control = World::getComponent<PlayerControl>(e);
                    auto& pos = World::getComponent<Position>(e);

                    if (!b2Body_IsValid(body.body)) {
                        continue;
                    }

                    b2Vec2 velocity = b2Body_GetLinearVelocity(body.body);
                    //if falling, cant jump
                    if (velocity.y > 0.1f && !control.isOnLadder) {
                        control.canJump = false;
                    }
                    if (control.isOnLadder) {
                        control.canJump = true;
                    }

                }
            }
        }

    private:
        static inline Mask mask = MaskBuilder()
            .set<Body>()
            .set<PlayerControl>()
            .set<Position>()
            .build();
    };

} // donkeykong

#endif //GROUNDEDSYSTEM_H