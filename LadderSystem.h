#ifndef LADDERSYSTEM_H
#define LADDERSYSTEM_H

#include "bagel.h"
#include "Components.h"
#include "InputSystem.h"
#include <vector>
#include <iostream>

using namespace bagel;

namespace donkeykong {

struct LadderInfo {
    int x, y;
    int width, height;

    LadderInfo(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height) {}

    bool isEntityOnLadder(int entityX, int entityY) const {
        bool result = (entityX >= x - width/2 - 5 &&
                entityX <= x + width/2 + 5 &&
                entityY >= y - height/2 &&
                entityY <= y + height/2);

        return result;
    }
};

class LadderSystem {
public:
    LadderSystem() = default;
    void addLadder(int x, int y, int width, int height) {
        ladders.emplace_back(x, y, width, height);
        std::cout << "Added ladder at (" << x << "," << y << ") with dimensions "
                  << width << "x" << height << std::endl;
    }

    void clearLadders() {
        ladders.clear();
    }

    void update() {
        for (ent_type e{0}; e.id <= World::maxId().id; ++e.id) {
            if (World::mask(e).test(mask)) {
                auto& control = World::getComponent<PlayerControl>(e);
                auto& pos = World::getComponent<Position>(e);

                bool onLadder = false;
                int ladder_index = -1;
                for (const auto& ladder : ladders) {
                    ladder_index++;
                    if (ladder.isEntityOnLadder(pos.x, pos.y)) {
                        onLadder = true;
                        break;
                    }
                }

                if (onLadder != control.isOnLadder) {
                    control.isOnLadder = onLadder;
                    if (onLadder) {
                        //std::cout << "Entity at (" << pos.x << "," << pos.y << ") is now on a ladder!" << std::endl;
                    } else {
                        //std::cout << "Entity at (" << pos.x << "," << pos.y << ") is no longer on a ladder." << std::endl;
                    }
                }
            }
        }
    }

private:
    std::vector<LadderInfo> ladders;

    static inline Mask mask = MaskBuilder()
        .set<PlayerControl>()
        .set<Position>()
        .build();
};

} // donkeykong

#endif //LADDERSYSTEM_H