#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H
#include "bagel.h"
#include "Components.h"
#include <SDL3/SDL_render.h>

using namespace bagel;

namespace donkeykong {

class RenderSystem {

public:
    void setRenderer(SDL_Renderer* renderer) {
        this->renderer = renderer;
    }
    void update();

private:
    SDL_Renderer* renderer;

     static inline Mask mask = MaskBuilder()
    .set<Position>()
    .set<Drawable>()
    .build();
};

} // donkeykong

#endif //RENDERSYSTEM_H
