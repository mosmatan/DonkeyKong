#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "bagel.h"
#include "Components.h"

using  namespace bagel;
namespace donkeykong {

    class Background : NoInstance{

    public:

        static Entity createBackground(SDL_Renderer* /*ren*/, SDL_Texture* tex) {

            auto entity =  Entity::create();

            entity.addAll(
                Drawable{tex, {10, 365,230,270}, 3.f,3.f, true},
                Position{175,150}
            );

            return entity;
        }


    };

} // donkeykong

#endif //BACKGROUND_H