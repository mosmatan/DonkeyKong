//
// Created by Matan Moskovich on 14/05/2025.
//

#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H
#include "bagel.h"
#include "Components.h"
#include "box2d/box2d.h"
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
        // Step the Box2D physics simulation
        if (!b2World_IsValid(boxWorld)) {
            std::cerr << "Error: Invalid Box2D world!" << std::endl;
            return;
        }

        // Print debug info for the first few frames
        static int frameCount = 0;
        if (frameCount < 5) {
            std::cout << "Physics frame " << frameCount << ": Stepping Box2D world" << std::endl;
            frameCount++;
        }

        b2World_Step(boxWorld, timeStep, 8); // Only 3 arguments, not 4

        // Update position of all entities that have both a Body and Position component
        for (ent_type e{0}; e.id <= World::maxId().id; ++e.id) {
            if (World::mask(e).test(mask)) {
                auto& body = World::getComponent<Body>(e);
                auto& pos = World::getComponent<Position>(e);

                // Skip invalid bodies
                if (!b2Body_IsValid(body.body)) {
                    continue;
                }

                // Get position from Box2D body
                b2Vec2 position = b2Body_GetPosition(body.body);

                // Debug output for the first few updates of each entity
                if (frameCount < 5) {
                    std::cout << "Entity " << e.id << " position: "
                              << position.x << ", " << position.y << std::endl;
                }

                // Update entity position from physics body (scale from physics units to pixel units)
                pos.x = static_cast<int>(position.x * boxScale);
                pos.y = static_cast<int>(position.y * boxScale);
            }
        }
    }

private:
    b2WorldId boxWorld;
    float boxScale;

    // Mask for entities with both Position and Body components
    static inline Mask mask = MaskBuilder()
        .set<Position>()
        .set<Body>()
        .build();
};

} // donkeykong

#endif //PHYSICSSYSTEM_H