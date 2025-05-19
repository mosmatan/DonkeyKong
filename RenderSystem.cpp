#include "RenderSystem.h"

#include "Components.h"

namespace donkeykong {

    void RenderSystem::update() {
        SDL_RenderClear(renderer);

        //Render green screen
        //SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

        for (ent_type e{0}; e.id <= World::maxId().id; ++e.id) {
            if (World::mask(e).test(mask)) {
                const auto& d = World::getComponent<Drawable>(e);
                const auto& t = World::getComponent<Position>(e);

                const SDL_FRect dst = {
                t.x - d.part.w / 2,
                    t.y - d.part.h / 2,
                    d.part.w * d.scaleX,
                    d.part.h * d.scaleY
                };

                SDL_FlipMode flip = d.flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

                SDL_RenderTextureRotated(
                    renderer, d.tex, &d.part, &dst, 0,
                    nullptr, flip);
            }
        }

        SDL_RenderPresent(renderer);

    }
} // donkeykong