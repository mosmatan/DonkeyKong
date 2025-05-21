//
// Created by Matan Moskovich on 20/05/2025.
//

#ifndef COLLOSIONSYSTEM_H
#define COLLOSIONSYSTEM_H
#include <iostream>

#include "bagel.h"
#include "BarrelSpawnSystem.h"
#include "InputSystem.h"

using namespace bagel;

namespace donkeykong {

class CollosionSystem {

    Mask _mask;
    Mask _barralCollosionMask;
    BarrelSpawnSystem* _barrelSpawnSystem = nullptr;

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

    void respawnBarrels(int barrelCount, ent_type e);

    void respawnMario(ent_type entity, ent_type other, bool entityIsMario);

    void restartGame(ent_type entity, ent_type other, bool entityIsMario);

    void handleCollision(int entityId, int otherId);



public:
    CollosionSystem() {

        MaskBuilder maskBuilder;
        maskBuilder.set<CollosionDetector>()
        .set<Position>();

        _mask = maskBuilder.build();

        maskBuilder.set<BarrelMove>();

        _barralCollosionMask = maskBuilder.build();
    }

    void setBarrelSpawnSystem(BarrelSpawnSystem* barrelSpawnSystem) {
        _barrelSpawnSystem = barrelSpawnSystem;
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


/*
 *
 * void handleCollision(int entityId, int otherId) {
    // Get entity types
    ent_type entity{static_cast<id_type>(entityId)};
    ent_type other{static_cast<id_type>(otherId)};

    // Check if one entity is Mario (has PlayerControl) and the other is a barrel (has BarrelMove)
    bool entityIsMario = World::mask(entity).test(Component<PlayerControl>::Bit);
    bool otherIsMario = World::mask(other).test(Component<PlayerControl>::Bit);
    bool entityIsBarrel = World::mask(entity).test(Component<BarrelMove>::Bit);
    bool otherIsBarrel = World::mask(other).test(Component<BarrelMove>::Bit);

    // If Mario collided with a barrel
    if ((entityIsMario && otherIsBarrel) || (entityIsBarrel && otherIsMario)) {
        ent_type mario = entityIsMario ? entity : other;

        std::cout << "Mario hit a barrel! Restarting..." << std::endl;

        // Reset Mario's position
        auto& marioPos = World::getComponent<Position>(mario);
        auto& marioBody = World::getComponent<Body>(mario);

        // Mario's initial position (from MarioEntity.h)
        const int initialX = 125;
        const int initialY = 575;

        // Update position
        marioPos.x = initialX;
        marioPos.y = initialY;

        // Update physics body position
        b2Vec2 newPosition = {initialX / Game::BOX_SCALE, initialY / Game::BOX_SCALE};
        b2Rot rotation = b2Body_GetTransform(marioBody.body).q;
        b2Body_SetTransform(marioBody.body, newPosition, rotation);

        // Reset velocity
        b2Vec2 zeroVelocity = {0, 0};
        b2Body_SetLinearVelocity(marioBody.body, zeroVelocity);

        //want distance between barrels when restart
        int barrelCount = 0;

        for (ent_type e{0}; e.id <= World::maxId().id; ++e.id) {
            if (World::mask(e).test(Component<BarrelMove>::Bit)) {
                auto& barrelPos = World::getComponent<Position>(e);
                auto& barrelBody = World::getComponent<Body>(e);
                auto& respawn = World::getComponent<RespawnWhen>(e);

                // Get the respawn threshold (when_y)
                int respawnThreshold = respawn.when_y; // Should be 750

                //put barrels above threshold in a distance between eachother to respawn one after another after they fall below threshol
                int yPosition = respawnThreshold - 200 - (barrelCount * 150);
                int xPosition = 2500; //so not draw the barrel when they fall off the screen

                // Update position
                barrelPos.x = xPosition;
                barrelPos.y = yPosition;

                // Update physics body
                b2Vec2 newBarrelPos = {xPosition / Game::BOX_SCALE, yPosition / Game::BOX_SCALE};
                b2Rot barrelRot = b2Body_GetTransform(barrelBody.body).q;
                b2Body_SetTransform(barrelBody.body, newBarrelPos, barrelRot);

                // Reset velocity
                b2Vec2 resetVel = {0, 0};
                b2Body_SetLinearVelocity(barrelBody.body, resetVel);

                // Increment counter for next barrel
                barrelCount++;
            }
        }
    }

    std::cout << "Collision detected between " << entityId << " and " << otherId << std::endl;
}
 */
