//
// Created by Matan Moskovich on 14/05/2025.
//

#include "Game.h"

#include <iostream>
#include <SDL3_image/SDL_image.h>

#include "Background.h"
#include "bagel.h"
#include "MarioEntity.h"


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

        // Box2D world
        b2WorldDef worldDef = b2DefaultWorldDef();
        worldDef.gravity = {0, 2.0f}; // Reduced gravity for testing
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
        SDL_SetRenderDrawColor(ren, 0,0,0,255);
        auto start = SDL_GetTicks();
        bool quit = false;

        std::cout << "Entering game loop..." << std::endl;

        try {
            while (!quit) {
                // Update physics - with reduced gravity for testing
                physicsSystem.update(PHYSICS_TIME_STEP);

                // Render frame
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
        } catch (const std::exception& e) {
            std::cerr << "Exception in game loop: " << e.what() << std::endl;
            SDL_Delay(5000); // Keep window open for 5 seconds to see error
        } catch (...) {
            std::cerr << "Unknown exception in game loop!" << std::endl;
            SDL_Delay(5000); // Keep window open for 5 seconds to see error
        }

        std::cout << "Exiting game loop..." << std::endl;
    }

    void Game::createEntities() {
        try {
            std::cout << "Creating background..." << std::endl;
            auto bg = Background::createBackground(ren, tex);
            std::cout << "Background created with ID: " << bg.entity().id << std::endl;

            // Create platforms based on the background image
            createPlatforms();

            std::cout << "Creating Mario..." << std::endl;
            // Position Mario just above the bottom platform
            auto mario = MarioEntity::create(tex);
            std::cout << "Mario created with ID: " << mario.entity().id << std::endl;

            // Validate that Mario has all required components
            if (!mario.has<Body>() || !mario.has<Position>()) {
                std::cerr << "Error: Mario is missing required components!" << std::endl;
            }

            // Validate that Mario's body is valid
            auto& body = mario.get<Body>();
            if (!b2Body_IsValid(body.body)) {
                std::cerr << "Error: Mario's physics body is invalid!" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Exception during entity creation: " << e.what() << std::endl;
            SDL_Delay(5000); // Keep window open for 5 seconds to see error
        } catch (...) {
            std::cerr << "Unknown exception during entity creation!" << std::endl;
            SDL_Delay(5000); // Keep window open for 5 seconds to see error
        }
    }

    void Game::createPlatforms() {
        PlatformEntity::createPlatform(boxWorld, 400, 705, 800, 20, BOX_SCALE); //platform mario land on
        PlatformEntity::createPlatform(boxWorld, 400, 655, 750, 15, BOX_SCALE);
        PlatformEntity::createPlatform(boxWorld, 400, 555, 750, 15, BOX_SCALE);
        PlatformEntity::createPlatform(boxWorld, 400, 455, 750, 15, BOX_SCALE);
        PlatformEntity::createPlatform(boxWorld, 400, 355, 750, 15, BOX_SCALE);
        PlatformEntity::createPlatform(boxWorld, 400, 255, 750, 15, BOX_SCALE);
        PlatformEntity::createPlatform(boxWorld, 400, 155, 750, 15, BOX_SCALE);
    }
}