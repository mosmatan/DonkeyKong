#include "Game.h"
#include <iostream>
#include <SDL3_image/SDL_image.h>

#include "Background.h"
#include "GameBottom.h"
#include "Kong.h"
#include "MarioEntity.h"
#include "PlatformEntity.h"
#include "Princess.h"

using namespace bagel;

namespace donkeykong {

    Game::Game() : physicsSystem(b2_nullWorldId, BOX_SCALE) {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            std::cout << SDL_GetError() << std::endl;
        }

        if (!SDL_CreateWindowAndRenderer(
            "Donkey Kong", WIN_WIDTH, WIN_HEIGHT, 0, &win, &ren)) {
            std::cout << SDL_GetError() << std::endl;
            }

        SDL_Surface *surf = IMG_Load("res/donkeykong.png");
        if (surf == nullptr) {
            std::cout << SDL_GetError() << std::endl;
            return;
        }

        tex = SDL_CreateTextureFromSurface(ren, surf);
        if (tex == nullptr) {
            std::cout << SDL_GetError() << std::endl;
            return;
        }
        SDL_DestroySurface(surf);

        b2WorldDef worldDef = b2DefaultWorldDef();
        worldDef.gravity = {0, 10.0f};
        boxWorld = b2CreateWorld(&worldDef);

        renderSystem.setRenderer(ren);
        physicsSystem.setWorld(boxWorld);
        physicsSystem.setScale(BOX_SCALE);
        barrelSpawnSystem.setTexture(tex);
    }

    Game::~Game() {
        if (b2World_IsValid(boxWorld))
            b2DestroyWorld(boxWorld);
        if (tex != nullptr)
            SDL_DestroyTexture(tex);
        if (ren != nullptr)
            SDL_DestroyRenderer(ren);
        if (win != nullptr)
            SDL_DestroyWindow(win);

        SDL_Quit();
    }

    bool Game::run() {
        createEntities();
        return gameLoop();
    }

    bool Game::gameLoop() {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        auto start = SDL_GetTicks();
        bool quit = false;

        while (!quit) {

            const Uint8* keyboardState = reinterpret_cast<const Uint8*>(SDL_GetKeyboardState(NULL));
            barrelSpawnSystem.update(PHYSICS_TIME_STEP);
            physicsSystem.update(PHYSICS_TIME_STEP);
            collosionSystem.update();
            platformSystem.update();
            ladderSystem.update();
            inputSystem.update(keyboardState);
            barrelMoveSystem.update();
            physicsSystem.update(PHYSICS_TIME_STEP);
            respownSystem.update();
            animationSystem.update(PHYSICS_TIME_STEP);
            renderSystem.update();

            auto end = SDL_GetTicks();
            if (end-start < GAME_FRAME) {
                SDL_Delay(GAME_FRAME - (end-start));
            }
            start += GAME_FRAME;

            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_EVENT_QUIT)
                    quit = true;
                else if ((e.type == SDL_EVENT_KEY_DOWN) && (e.key.scancode == SDL_SCANCODE_ESCAPE))
                    quit = true;
            }
        }

        return quit;
    }

    void Game::createEntities() {
        Background::createBackground(ren, tex);
        GameBottom::create(750);
        createPlatforms();
        createLadders();
        Kong::create(tex, 380, 155);
        MarioEntity::create(tex);
        Princess::create(tex, 555, 197);

    }

    void Game::createPlatforms() {
        PlatformEntity::createPlatform(boxWorld, 400, 700, 700, 20, BOX_SCALE);
        PlatformEntity::createPlatform(boxWorld, 236, 576, 260, 20, BOX_SCALE);
        PlatformEntity::createPlatform(boxWorld, 464, 576, 130, 20, BOX_SCALE);
        PlatformEntity::createPlatform(boxWorld, 614, 576, 110, 20, BOX_SCALE);
        PlatformEntity::createPlatform(boxWorld, 175, 452, 100, 20, BOX_SCALE);
        PlatformEntity::createPlatform(boxWorld, 395, 452, 195, 20, BOX_SCALE);
        PlatformEntity::createPlatform(boxWorld, 600, 452, 85, 20, BOX_SCALE);
        PlatformEntity::createPlatform(boxWorld, 260, 337, 185, 20, BOX_SCALE);
        PlatformEntity::createPlatform(boxWorld, 510, 337, 220, 20, BOX_SCALE);
        PlatformEntity::createPlatform(boxWorld, 217, 215, 40, 20, BOX_SCALE);
        PlatformEntity::createPlatform(boxWorld, 390, 215, 220, 20, BOX_SCALE);
        PlatformEntity::createPlatform(boxWorld, 575, 215, 50, 20, BOX_SCALE);



        platformSystem.addPlatform(400, 700, 700, 10);
        platformSystem.addPlatform(236, 576, 260, 10);
        platformSystem.addPlatform(464, 576, 130, 10);
        platformSystem.addPlatform(614, 576, 110, 10);
        platformSystem.addPlatform(175, 452, 100, 10);
        platformSystem.addPlatform(395, 452, 195, 10);
        platformSystem.addPlatform(600, 452, 85, 10);
        platformSystem.addPlatform(260, 337, 185, 10);
        platformSystem.addPlatform(510, 337, 220, 10);
        platformSystem.addPlatform(217, 215, 40, 10);
        platformSystem.addPlatform(390, 215, 220, 10);
        platformSystem.addPlatform(575, 215, 50, 10);
    }

    void Game::createLadders() {
        ladderSystem.addLadder(92, 645, 10, 180);
        ladderSystem.addLadder(380, 645, 10, 180);
        ladderSystem.addLadder(693, 645, 10, 180);
        ladderSystem.addLadder(115, 500, 10, 125);
        ladderSystem.addLadder(285, 500, 10, 125);
        ladderSystem.addLadder(502, 500, 10, 125);
        ladderSystem.addLadder(668, 500, 10, 125);
        ladderSystem.addLadder(140, 380, 10, 125);
        ladderSystem.addLadder(380, 380, 10, 125);
        ladderSystem.addLadder(643, 380, 10, 125);
        ladderSystem.addLadder(160, 250, 10, 125);
        ladderSystem.addLadder(260, 250, 10, 125);
        ladderSystem.addLadder(526, 250, 10, 125);
        ladderSystem.addLadder(620, 250, 10, 125);
    }
}