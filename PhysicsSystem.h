#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include <SDL3/SDL.h>
#include "bagel.h"
#include "Components.h"
#include <box2d/box2d.h>
#include <iostream>

using namespace bagel;

namespace donkeykong {

class PhysicsSystem {
public:
    PhysicsSystem(b2WorldId world = b2_nullWorldId, float scale = 10.0f)
        : boxWorld(world), boxScale(scale) {}

    void setWorld(b2WorldId world) {
        this->boxWorld = world;
    }

    void setScale(float scale) {
        this->boxScale = scale;
    }

    void update(float timeStep) {
        if (!b2World_IsValid(boxWorld)) {
            std::cerr << "Error: Invalid Box2D world!" << std::endl;
            return;
        }

        const int subStepCount = 16;

        b2World_Step(boxWorld, timeStep, subStepCount);
        for (ent_type e{0}; e.id <= World::maxId().id; ++e.id) {
            if (World::mask(e).test(mask)) {

                auto& body = World::getComponent<Body>(e);
                auto& pos = World::getComponent<Position>(e);

                if (!b2Body_IsValid(body.body)) {
                    continue;
                }
                b2Vec2 position = b2Body_GetPosition(body.body);
                //update entity position from physics body
                pos.x = static_cast<int>(position.x * boxScale);
                pos.y = static_cast<int>(position.y * boxScale);
            }
        }
    }

private:
    b2WorldId boxWorld;
    float boxScale;

     Mask mask = MaskBuilder()
        .set<Position>()
        .set<Body>()
        .build();
};

} // donkeykong

#endif //PHYSICSSYSTEM_H