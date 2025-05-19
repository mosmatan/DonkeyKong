//
// Created by Matan Moskovich on 19/05/2025.
//

#ifndef BARRELMOVESYSTEM_H
#define BARRELMOVESYSTEM_H
#include "bagel.h"
#include "Components.h"
#include <random>

#include "box2d/box2d.h"

using namespace bagel;

namespace donkeykong {

class BarrelMoveSystem {

    Mask _mask;

    // A helper that returns a random integer in [min, max] inclusive
    int randomIntInRange(int min, int max) {
        // Note: make these static so the engine is only seeded once
        static std::random_device rd;
        static std::mt19937       gen(rd());

        std::uniform_int_distribution<> dist(min, max);
        return dist(gen);
    }

public:
    BarrelMoveSystem() {
        _mask = MaskBuilder()
        .set<Body>()
        .set<BarrelMove>()
        .set<Moveable>()
        .build();
    }

    void update() {
        for (ent_type e{0}; e.id <= World::maxId().id; ++e.id) {
            if (World::mask(e).test(_mask)) {
                auto& body = World::getComponent<Body>(e);
                auto& barrelMove = World::getComponent<BarrelMove>(e);
                auto& moveable = World::getComponent<Moveable>(e);

                if (!b2Body_IsValid(body.body)) {
                    continue;
                }

                b2Vec2 velocity = b2Body_GetLinearVelocity(body.body);

                if (velocity.y > 1.5f) {
                    barrelMove.isFalling = true;
                    //std::cout << "barrelMove.isFalling" << std::endl;
                }

                if (!barrelMove.isFalling) {
                    velocity.x = (int)barrelMove.direction * barrelMove.moveSpeed;
                }

                if (barrelMove.isFalling && velocity.y < 0.5f) {
                    //std::cout << "Barrel is stop falling" << std::endl;
                    barrelMove.isFalling = false;

                    int dir = 2 * randomIntInRange(0, 1) - 1;
                    barrelMove.direction = dir;

                    velocity.x = dir * barrelMove.moveSpeed;
                }
                b2Body_SetLinearVelocity(body.body, velocity);
            }
        }
    }

};

} // donkeykong

#endif //BARRELMOVESYSTEM_H
