//
// Created by Matan Moskovich on 21/05/2025.
//

#ifndef PRINCESS_H
#define PRINCESS_H
#include "bagel.h"

using namespace bagel;

namespace donkeykong {

class Princess : NoInstance{

    static constexpr float TEX_SCALE_WIDTH_PRINCESS = 1.f;
    static constexpr float TEX_SCALE_HEIGHT_PRINCESS = 1.f;
    static constexpr float PRINCESS_BODY_WIDTH = 14;
    static constexpr float PRINCESS_BODY_HEIGHT = 18;

    static inline Drawable** PRINCESS_ANIMATION = nullptr;

public:

    static Entity create(SDL_Texture* tex, int x, int y) {
        PRINCESS_ANIMATION = new Drawable*[1] {
            new Drawable[8] { // IDLE
                {tex,SDL_FRect{10, 10, 20, 40},TEX_SCALE_WIDTH_PRINCESS,TEX_SCALE_HEIGHT_PRINCESS,true,},
                {tex,SDL_FRect{10, 10, 20, 40},TEX_SCALE_WIDTH_PRINCESS,TEX_SCALE_HEIGHT_PRINCESS,true,},
                {tex,SDL_FRect{10, 10, 20, 40},TEX_SCALE_WIDTH_PRINCESS,TEX_SCALE_HEIGHT_PRINCESS,true,},
                {tex,SDL_FRect{10, 10, 20, 40},TEX_SCALE_WIDTH_PRINCESS,TEX_SCALE_HEIGHT_PRINCESS,true,},
                {tex,SDL_FRect{90, 10, 50, 40},TEX_SCALE_WIDTH_PRINCESS,TEX_SCALE_HEIGHT_PRINCESS,true,},
                {tex,SDL_FRect{90, 10, 50, 40},TEX_SCALE_WIDTH_PRINCESS,TEX_SCALE_HEIGHT_PRINCESS,true,},
                {tex,SDL_FRect{90, 10, 50, 40},TEX_SCALE_WIDTH_PRINCESS,TEX_SCALE_HEIGHT_PRINCESS,true,},
                {tex,SDL_FRect{90, 10, 50, 40},TEX_SCALE_WIDTH_PRINCESS,TEX_SCALE_HEIGHT_PRINCESS,true,}
            }
        };

        Entity princess = Entity::create();
        princess.add<Position>({x,y});
        princess.add<Drawable>(
            {
                tex,
                SDL_FRect{245, 70, 14, 18},
                TEX_SCALE_WIDTH_PRINCESS,
                TEX_SCALE_HEIGHT_PRINCESS,
                true
            });

        princess.add<Animation>({
            PRINCESS_ANIMATION,
            1,
            8,
            0,
            0,
            Animation::type::PRINCESS
        });

        princess.add<CollosionDetector>({0, PRINCESS_BODY_WIDTH / 2, PRINCESS_BODY_HEIGHT/3});
        princess.add<PrincessComponent>({});

        return princess;
    }

};

} // dinkeykong

#endif //PRINCESS_H
