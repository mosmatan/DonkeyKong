//
// Created by Matan Moskovich on 14/05/2025.
//

#ifndef GAME_H
#define GAME_H
#include <SDL3/SDL_render.h>

#include <SDL3/SDL.h>
#include <box2d/box2d.h>

#include "RenderSystem.h"
#include "PhysicsSystem.h"
#include "PlatformEntity.h"

namespace donkeykong {

    class Game {

    public:
        static constexpr float	BOX_SCALE = 10;
        static inline b2WorldId boxWorld = b2_nullWorldId;

        Game();
        ~Game();
        void run();


    private:


        static constexpr int	WIN_WIDTH = 800;
        static constexpr int	WIN_HEIGHT = 800;
        static constexpr int	FPS = 60;

        static constexpr float	GAME_FRAME = 1000.f/FPS;
        static constexpr float  PHYSICS_TIME_STEP = 1.0f / FPS;


        SDL_Texture* tex;
        SDL_Renderer* ren;
        SDL_Window* win;

        RenderSystem renderSystem;
        PhysicsSystem physicsSystem;

        void gameLoop();
        void createEntities();
        void createPlatforms();

    };

} // donkeykong

#endif //GAME_H