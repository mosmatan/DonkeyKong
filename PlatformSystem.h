﻿#ifndef PLATFORM_SYSTEM_H
#define PLATFORM_SYSTEM_H

#include "bagel.h"
#include "Components.h"
#include "InputSystem.h"
#include <box2d/box2d.h>
#include <iostream>
#include <vector>

using namespace bagel;

namespace donkeykong {

struct PlatformInfo {
    int x, y;
    int width;
    int height;

    PlatformInfo(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height) {}

    bool isEntityOnPlatform(int entityX, int entityY, int entityHeight) const {
        int halfWidth = width / 2;
        int halfHeight = height / 2;
        int entityBottom = entityY + entityHeight / 2;

        bool horizontalOverlap = (entityX >= x - halfWidth) && (entityX <= x + halfWidth);

        bool verticalPosition = std::abs(entityBottom - (y - halfHeight)) < 5;

        return horizontalOverlap && verticalPosition;
    }
};

class PlatformSystem {
public:
    PlatformSystem() = default;

    void addPlatform(int x, int y, int width, int height) {
        platforms.emplace_back(x, y, width, height);
        std::cout << "Added platform at (" << x << "," << y << ") with dimensions "
                  << width << "x" << height << std::endl;
    }

    void clearPlatforms() {
        platforms.clear();
    }

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
                bool onPlatform = false;

                const int entityHeight = 30; // Approximate Mario height

                for (const auto& platform : platforms) {
                    if (platform.isEntityOnPlatform(pos.x, pos.y, entityHeight)) {
                        onPlatform = true;
                        //move entity to be on platform
                        // pos.y = platform.y - platform.height/2 - entityHeight/2;
                        // velocity.y = 0;
                        // b2Body_SetLinearVelocity(body.body, velocity);
                        break;
                    }
                }

                if (onPlatform && !control.canJump) {
                    control.canJump = true;
                } else if (!onPlatform && control.canJump && velocity.y > 0.1f) {
                    control.canJump = false;
                }
            }
        }
    }

private:
    std::vector<PlatformInfo> platforms;

    static inline Mask mask = MaskBuilder()
        .set<Body>()
        .set<PlayerControl>()
        .set<Position>()
        .build();
};

}

#endif //PLATFORM_SYSTEM_H