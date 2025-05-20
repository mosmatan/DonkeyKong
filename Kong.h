//
// Created by Matan Moskovich on 20/05/2025.
//

#ifndef KONG_H
#define KONG_H
#include "bagel.h"

using namespace bagel;

namespace donkeykong {

class Kong : NoInstance {

    static constexpr float TEX_SCALE_WIDTH_KONG = 2.2f;
    static constexpr float TEX_SCALE_HEIGHT_KONG = 2.2f;
    static constexpr float KONG_BODY_WIDTH = 14;
    static constexpr float KONG_BODY_HEIGHT = 18;

    static inline Drawable** KONG_ANIMATION = nullptr;



public:

    static Entity create(SDL_Texture* tex, int x, int y) {
        KONG_ANIMATION = new Drawable*[1] {
            new Drawable[4] { // IDLE
                {tex,SDL_FRect{10, 50, 50, 50},TEX_SCALE_WIDTH_KONG,TEX_SCALE_HEIGHT_KONG,true,},
                {tex,SDL_FRect{119, 50, 50, 50},TEX_SCALE_WIDTH_KONG,TEX_SCALE_HEIGHT_KONG,true,},
                {tex,SDL_FRect{10, 50, 50, 50},TEX_SCALE_WIDTH_KONG,TEX_SCALE_HEIGHT_KONG,true,},
                {tex,SDL_FRect{170, 50, 50, 50},TEX_SCALE_WIDTH_KONG,TEX_SCALE_HEIGHT_KONG,true,},
            }
        };

        Entity kong = Entity::create();
        kong.add<Position>({x,y});
        kong.add<Drawable>(
            {
                tex,
                SDL_FRect{245, 70, 14, 18},
                TEX_SCALE_WIDTH_KONG,
                TEX_SCALE_HEIGHT_KONG,
                true
            });

        kong.add<Animation>({
            KONG_ANIMATION,
            2,
            4,
            0,
            0,
            Animation::type::KONG
        });

        return kong;
    }

};

} // donkeykong

#endif //KONG_H
