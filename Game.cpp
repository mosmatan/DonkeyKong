#include "Game.h"

#include <iostream>
#include <SDL3_image/SDL_image.h>

#include "Background.h"
#include "bagel.h"
#include "MarioEntity.h"
#include "PlatformEntity.h"

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
        worldDef.gravity = {0, 10.0f}; // Set gravity
        boxWorld = b2CreateWorld(&worldDef);

        renderSystem.setRenderer(ren);
        physicsSystem.setWorld(boxWorld);
        physicsSystem.setScale(BOX_SCALE);
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

    void Game::run() {
        createEntities();
        gameLoop();
    }

    void Game::gameLoop() {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        auto start = SDL_GetTicks();
        bool quit = false;

        while (!quit) {

            const Uint8* keyboardState = reinterpret_cast<const Uint8*>(SDL_GetKeyboardState(NULL));
            platformSystem.update();
            ladderSystem.update();
            inputSystem.update(keyboardState);
            physicsSystem.update(PHYSICS_TIME_STEP);
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
    }

    void Game::createEntities() {
        Background::createBackground(ren, tex);
        createPlatforms();
        createLadders();
        MarioEntity::create(tex);
    }

    void Game::createPlatforms() {
        PlatformEntity::createPlatform(boxWorld, 400, 700, 700, 10, BOX_SCALE);
        platformSystem.addPlatform(50, 694, 750, 700);

        PlatformEntity::createPlatform(boxWorld, 400, 600, 700, 10, BOX_SCALE);
        platformSystem.addPlatform(50, 600, 750, 600);

        PlatformEntity::createPlatform(boxWorld, 400, 500, 700, 10, BOX_SCALE);
        platformSystem.addPlatform(50, 500, 750, 500);

        PlatformEntity::createPlatform(boxWorld, 400, 400, 700, 10, BOX_SCALE);
        platformSystem.addPlatform(50, 400, 750, 400);

        PlatformEntity::createPlatform(boxWorld, 400, 300, 700, 10, BOX_SCALE);
        platformSystem.addPlatform(50, 300, 750, 300);

        PlatformEntity::createPlatform(boxWorld, 400, 200, 700, 10, BOX_SCALE);
        platformSystem.addPlatform(50, 200, 750, 200);

        PlatformEntity::createPlatform(boxWorld, 400, 100, 700, 10, BOX_SCALE);
        platformSystem.addPlatform(50, 100, 750, 100);

    }

    void Game::createLadders() {
        ladderSystem.addLadder(635, 650, 20, 100);
        ladderSystem.addLadder(650, 550, 20, 100);
        ladderSystem.addLadder(250, 450, 20, 100);
        ladderSystem.addLadder(600, 350, 20, 100);
        ladderSystem.addLadder(200, 250, 20, 100);
        ladderSystem.addLadder(550, 150, 20, 100);
    }
}