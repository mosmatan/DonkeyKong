//
// Created by Matan Moskovich on 11/05/2025.
//

#include "Game.h"

#include <iostream>
#include <SDL3_image/SDL_image.h>

#include "Background.h"
#include "bagel.h"
#include "MarioEntity.h"


using namespace bagel;

namespace donkeykong {
    Game::Game() {
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

        // Box2D world
        b2WorldDef worldDef = b2DefaultWorldDef();
        worldDef.gravity = {0,0};
        boxWorld = b2CreateWorld(&worldDef);



        renderSystem.setRenderer(ren);
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
        SDL_SetRenderDrawColor(ren, 0,0,0,255);
        auto start = SDL_GetTicks();
        bool quit = false;

        while (!quit) {

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
        MarioEntity::create(tex);
    }
}
