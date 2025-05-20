//
// Created by Matan Moskovich on 20/05/2025.
//

#ifndef COLLOSIONSYSTEM_H
#define COLLOSIONSYSTEM_H
#include <iostream>

#include "bagel.h"
#include "InputSystem.h"

using namespace bagel;

namespace donkeykong {

class CollosionSystem {

    Mask _mask;
    Mask _barralCollosionMask;

bool isColliding(const Position& pos1, const CollosionDetector& dec1,
                 const Position& pos2, const CollosionDetector& dec2) {

    return
        (pos1.x + dec1.width > pos2.x - dec2.width && // From the right
         pos1.x - dec1.width < pos2.x + dec2.width && // From the left
         pos1.y + dec1.height > pos2.y - dec2.height && // From below
         pos1.y - dec1.height < pos2.y + dec2.height); // From above
}

    void lookForCollisions(const ent_type& entity, CollosionDetector& detector, const Position& pos) {

        for (int j = 0; j < Storage<CollosionDetector>::type::size(); ++j) {
            const auto& other = Storage<CollosionDetector>::type::entity(j);
            if (entity.id == other.id) {
                continue; // Skip self-collision
            }

            auto& otherDetector = Storage<CollosionDetector>::type::get(j);
            const auto& otherPos = World::getComponent<Position>(other);
            if (!isColliding(pos, detector, otherPos, otherDetector)) {
                continue; // No collision
            }

            std::cout<< "Collision detected between " << entity.id << " and " << other.id << std::endl;

            detector.entities |= 1 << other.id;
            otherDetector.entities |= 1 << entity.id;
        }
    }

    void handleCollision(int entityId, int otherId) {
    // Handle the collision between entityId and otherId

    std::cout << "Collision detected between " << entityId << " and " << otherId << std::endl;
}



public:
    CollosionSystem() {

        MaskBuilder maskBuilder;
        maskBuilder.set<CollosionDetector>()
        .set<Position>();

        _mask = maskBuilder.build();

        maskBuilder.set<BarrelMove>();

        _barralCollosionMask = maskBuilder.build();
    }

    void update() {

        for (int i = 0; i < PackedStorage<CollosionDetector>::size(); ++i) {
            auto& detector = PackedStorage<CollosionDetector>::get(i);
            const auto& entity = PackedStorage<CollosionDetector>::entity(i);
            auto& pos = World::getComponent<Position>(entity);

            lookForCollisions(entity, detector, pos);

            while (detector.entities > 0) {

                int otherid =0;
                for (int j = 0; j < 32; ++j) {
                    if ((detector.entities & (1 << j)) != 0) {
                        otherid = j;
                        break;
                    }
                }

                handleCollision(entity.id, otherid);

                detector.entities &= ~(1 << otherid); // Clear the bit
            }
        }
    }

};

} // donkeykong

#endif //COLLOSIONSYSTEM_H
