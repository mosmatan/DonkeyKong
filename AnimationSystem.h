//
// Created by Matan Moskovich on 20/05/2025.
//

#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H
#include "bagel.h"

using namespace bagel;

namespace donkeykong {

class AnimationSystem {

    float _timeInterval = 0.15f;
    float _timeDuration = 0.0f;
    Mask _mask;
    Mask _bodyMask;

    void marioHandler(ent_type entity,Animation &marioAnim) {

        const auto& body = World::getComponent<Body>(entity);
        const auto& velocity = b2Body_GetLinearVelocity(body.body);

        marioAnim.currentState = (b2Length(velocity) > 1.f) ? 1 : 0; // WALK
    }

    void barrelHandler(ent_type entity, Animation &barrelAnim) {

        const auto& barrelMove = World::getComponent<BarrelMove>(entity);
        const auto& body = World::getComponent<Body>(entity);
        const auto& velocity = b2Body_GetLinearVelocity(body.body);

        barrelAnim.currentState = (velocity.y > 2.f) ? 1 : 0;
    }

public:
    AnimationSystem() {
        _mask = MaskBuilder()
            .set<Animation>()
            .set<Drawable>()
            .build();

        _bodyMask = MaskBuilder()
            .set<Body>()
            .build();
    }

    void update(float deltaTime) {

        _timeDuration += deltaTime;

        if (_timeDuration < _timeInterval) {
            return;
        }

        for (int i=0;i< Storage<Animation>::type::size(); ++i) {

            ent_type ent = Storage<Animation>::type::entity(i);

            if (!World::mask(ent).test(_mask)) {
                continue;
            }

            auto& anim = Storage<Animation>::type::get(i);

            if (World::mask(ent).test(_bodyMask)) {
                if (anim.animType == Animation::type::MARIO) {
                    marioHandler(ent, anim);
                }
                else if (anim.animType == Animation::type::BARREL) {
                    barrelHandler(ent, anim);
                }
            }

            auto& sprite = World::getComponent<Drawable>(ent);
            auto flip = sprite.flip;

            sprite = anim.states_frames[anim.currentState][anim.currentFrame];
            sprite.flip = flip;

            anim.currentFrame++;
            anim.currentFrame %= anim.framesCount;
        }

        _timeDuration =0;
    }

};

} // donkeykong

#endif //ANIMATIONSYSTEM_H
