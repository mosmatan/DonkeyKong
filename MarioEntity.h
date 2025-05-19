#ifndef MARIOENTITY_H
#define MARIOENTITY_H
#include "bagel.h"
#include "Components.h"
#include "Game.h"
#include "InputSystem.h"

using namespace bagel;

namespace donkeykong {

    class MarioEntity : NoInstance{

    private:
        static constexpr float TEX_SCALE_WIDTH_MARIO = 1.6f;
        static constexpr float TEX_SCALE_HEIGHT_MARIO = 1.6f;
        static constexpr float MARIO_BODY_WIDTH = 14;
        static constexpr float MARIO_BODY_HEIGHT = 21;

    public:

        static Entity create(SDL_Texture* tex) {

            Entity mario = Entity::create();

            Position position{125,575};

            b2BodyDef marioBodyDef = b2DefaultBodyDef();
            marioBodyDef.type = b2_dynamicBody;
            marioBodyDef.position = {position.x / Game::BOX_SCALE, position.y / Game::BOX_SCALE};
            b2BodyId marioBody = b2CreateBody(Game::boxWorld, &marioBodyDef);

            b2ShapeDef padShapeDef = b2DefaultShapeDef();
            padShapeDef.density = 1;

            b2Polygon padBox = b2MakeBox(MARIO_BODY_WIDTH/ Game::BOX_SCALE/2, MARIO_BODY_HEIGHT/Game::BOX_SCALE/2);
            b2CreatePolygonShape(marioBody, &padShapeDef, &padBox);

            mario.add<Position>(position);
            mario.add<Drawable>(
                {
                    tex,
                    SDL_FRect{16, 200, 14, 21},
                    TEX_SCALE_WIDTH_MARIO,
                    TEX_SCALE_HEIGHT_MARIO,
                    true,
                });
            mario.add<Moveable>({0,0});
            mario.add<Body>({marioBody});

            mario.add<PlayerControl>({false, false, 5.0f, 7.0f, 3.5f});

            return mario;
        }

    };

} // donkeykong

#endif //MARIOENTITY_H