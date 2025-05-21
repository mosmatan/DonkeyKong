//
// Created by Matan Moskovich on 21/05/2025.
//

#include "CollosionSystem.h"
#include "Game.h"

namespace donkeykong {

    void CollosionSystem::respawnBarrels(int barrelCount, ent_type e) {
        auto& barrelPos = World::getComponent<Position>(e);
        auto& barrelBody = World::getComponent<Body>(e);
        auto& respawn = World::getComponent<RespawnWhen>(e);

        // Get the respawn threshold (when_y)
        int respawnThreshold = respawn.when_y; // Should be 750

        //put barrels above threshold in a distance between eachother to respawn one after another after they fall below threshol
        int yPosition = respawnThreshold - 200 - (barrelCount * 1000);
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
    }

    void CollosionSystem::respawnMario(ent_type entity, ent_type other, bool entityIsMario) {
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
    }

    void CollosionSystem::restartGame(ent_type entity, ent_type other, bool entityIsMario) {
        respawnMario(entity, other, entityIsMario);

        //want distance between barrels when restart
        int barrelCount = 0;

        for (ent_type e{0}; e.id <= World::maxId().id; ++e.id) {
            if (World::mask(e).test(Component<BarrelMove>::Bit)) {
                respawnBarrels(barrelCount, e);
                ++barrelCount;
            }
        }
    }

    void CollosionSystem::handleCollision(int entityId, int otherId) {
        // Get entity types
        ent_type entity{static_cast<id_type>(entityId)};
        ent_type other{static_cast<id_type>(otherId)};

        // Check if one entity is Mario (has PlayerControl) and the other is a barrel (has BarrelMove)
        bool entityIsMario = World::mask(entity).test(Component<PlayerControl>::Bit);
        bool otherIsMario = World::mask(other).test(Component<PlayerControl>::Bit);
        bool entityIsBarrel = World::mask(entity).test(Component<BarrelMove>::Bit);
        bool otherIsBarrel = World::mask(other).test(Component<BarrelMove>::Bit);

        // check for princess
        bool entityIsPrincess = World::mask(entity).test(Component<PrincessComponent>::Bit);
        bool otherIsPrincess = World::mask(other).test(Component<PrincessComponent>::Bit);

        // add check for bottom
        bool entityIsBottom = World::mask(entity).test(Component<BottomComponent>::Bit);
        bool otherIsBottom = World::mask(other).test(Component<BottomComponent>::Bit);

        // If Mario collided with a barrel
        if ((entityIsMario && otherIsBarrel) || (entityIsBarrel && otherIsMario)) {
            std::cout << "Mario hit a barrel! Restarting..." << std::endl;
            restartGame(entity, other, entityIsMario);

            // future feature decrease life
        }
        else if ( (entityIsPrincess && otherIsMario) || (otherIsPrincess && entityIsMario)) {
            // Handle collision between Mario and Princess
            std::cout << "Mario reached the princess!" << std::endl;
            restartGame(entity, other, entityIsMario);

            // future feature add score
        }

        else if ( (entityIsBottom && otherIsMario) || (otherIsBottom && entityIsMario)) {
            // Handle collision between barrel and bottom
            std::cout << "Mario hit the bottom!" << std::endl;
            restartGame(entity, other, entityIsMario);

            // future feature
        }
        std::cout << "Collision detected between " << entityId << " and " << otherId << std::endl;
    }


}
