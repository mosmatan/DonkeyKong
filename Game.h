#ifndef GAME_H
#define GAME_H
#include <SDL3/SDL_render.h>

#include "AnimationSystem.h"
#include "BarrelMoveSystem.h"
#include "BarrelSpawnSystem.h"
#include "CollosionSystem.h"
#include "RenderSystem.h"
#include "PhysicsSystem.h"
#include "InputSystem.h"
#include "PlatformSystem.h"
#include "LadderSystem.h"
#include "RespawnSystem.h"


namespace donkeykong {

    class Game {

    public:
        static constexpr float BOX_SCALE = 10;
        static inline b2WorldId boxWorld = b2_nullWorldId;

        Game();
        ~Game();
        bool run();


    private:


        static constexpr int WIN_WIDTH = 800;
        static constexpr int WIN_HEIGHT = 800;
        static constexpr int FPS = 60;

        static constexpr float GAME_FRAME = 1000.f/FPS;
        static constexpr float PHYSICS_TIME_STEP = 1.0f / FPS;


        SDL_Texture* tex;
        SDL_Renderer* ren;
        SDL_Window* win;

        RenderSystem renderSystem;
        PhysicsSystem physicsSystem;
        InputSystem inputSystem;
        PlatformSystem platformSystem;
        LadderSystem ladderSystem;
        BarrelMoveSystem barrelMoveSystem;
        RespawnSystem respownSystem;
        BarrelSpawnSystem barrelSpawnSystem{tex, 3, 7.0f};
        CollosionSystem collosionSystem;
        AnimationSystem animationSystem;


        bool gameLoop();
        void createEntities();
        void createPlatforms();
        void createLadders();



    };

}

#endif //GAME_H