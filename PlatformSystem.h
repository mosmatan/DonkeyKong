#ifndef ANGLED_PLATFORM_SYSTEM_H
#define ANGLED_PLATFORM_SYSTEM_H

#include "bagel.h"
#include "Components.h"
#include "InputSystem.h"
#include <box2d/box2d.h>
#include <iostream>
#include <vector>

using namespace bagel;

namespace donkeykong {

struct PlatformInfo {
    int startX, startY;
    int endX, endY;
    float slope;

    PlatformInfo(int x1, int y1, int x2, int y2)
        : startX(x1), startY(y1), endX(x2), endY(y2) {
        if (x2 != x1) {
            slope = static_cast<float>(y2 - y1) / (x2 - x1);
        } else {
            slope = 0;
        }
    }

    //check if an x position is within this platform's range
    bool containsX(int x) const {
        return (x >= startX && x <= endX) || (x >= endX && x <= startX);
    }

    int getYAt(int x) const {
        if (startX == endX) return startY; // Avoid division by zero
        return startY + static_cast<int>(slope * (x - startX));
    }
};

class AngledPlatformSystem {
public:
    AngledPlatformSystem() = default;

    void addPlatform(int x1, int y1, int x2, int y2) {
        platforms.emplace_back(x1, y1, x2, y2);
        std::cout << "Added platform from (" << x1 << "," << y1 << ") to ("
                  << x2 << "," << y2 << ") with slope " << platforms.back().slope << std::endl;
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
                //check if mario is on a platform
                bool onPlatform = false;
                const PlatformInfo* currentPlatform = nullptr;

                for (const auto& platform : platforms) {
                    if (platform.containsX(pos.x)) {
                        int platformY = platform.getYAt(pos.x);
                        int marioFeet = pos.y + 15;
                        //check if mario is close to the platform height
                        if (std::abs(marioFeet - platformY) < 5 && velocity.y >= 0) {
                            onPlatform = true;
                            currentPlatform = &platform;
                            //adjust mario position to be on the platform
                            pos.y = platformY - 15;
                            velocity.y = 0;
                            b2Body_SetLinearVelocity(body.body, velocity);

                            break;
                        }
                    }
                }
                //update if mario can jump
                if (onPlatform && !control.canJump) {
                    control.canJump = true;
                } else if (!onPlatform && control.canJump && velocity.y > 0.1f) {
                    control.canJump = false;
                }

                //if mario is on a platform and moving right/left, adjust height because of angle
                if (onPlatform && currentPlatform && std::abs(velocity.x) > 0.01f) {
                    int newX = pos.x + static_cast<int>(velocity.x);
                    //check if still on the same platform
                    if (currentPlatform->containsX(newX)) {
                        int newY = currentPlatform->getYAt(newX) - 15; // 15 is Mario's height offset

                        pos.y = newY;
                    }
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

} // donkeykong

#endif //ANGLED_PLATFORM_SYSTEM_H