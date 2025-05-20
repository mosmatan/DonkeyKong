//
// Created by Matan Moskovich on 19/05/2025.
//

#ifndef RESPOWNSYSTEM_H
#define RESPOWNSYSTEM_H
#include "bagel.h"
#include "Components.h"
#include "box2d/box2d.h"
#include "Game.h"


using namespace bagel;

namespace donkeykong {

class RespawnSystem {

    Mask _mask;

public:
    RespawnSystem() {
        _mask = MaskBuilder()
        .set<Position>()
        .set<RespawnWhen>()
        .build();
    }

    void update() {

        for (int i=0; i < PackedStorage<RespawnWhen>::size(); i++) {
            auto& respawn = PackedStorage<RespawnWhen>::get(i);

            auto ent = PackedStorage<RespawnWhen>::entity(i);
            auto& pos = World::getComponent<Position>(ent);
            auto& body = World::getComponent<Body>(ent);

            bool triggerd = (respawn.above && pos.y > respawn.when_y) || (respawn.below && pos.y < respawn.when_y);

            if (triggerd) {
                std::cout << "Respawn triggered for entity: " << ent.id << std::endl;
                pos.y = respawn.respawn_y;
                pos.x = respawn.respawn_x;

                b2Vec2 new_postion;
                new_postion.x = pos.x /10.f;
                new_postion.y = pos.y /10.f;

                b2Rot rot = b2Body_GetTransform(body.body).q;

                std::cout << "Respawned entity: " << ent.id << " to position: (" << new_postion.x << ", " << new_postion.y << ")" << std::endl;

                b2Body_SetTransform(body.body, new_postion,rot);

            }
        }
    }

};

} // donkeykong
#endif //RESPOWNSYSTEM_H
