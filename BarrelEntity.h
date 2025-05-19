//
// Created by Matan Moskovich on 19/05/2025.
//

#ifndef BARREL_H
#define BARREL_H
#include "bagel.h"
#include "Components.h"
#include "Game.h"

using namespace bagel;

namespace donkeykong {

class BarrelEntity {

private:

    static constexpr float TEX_SCALE_WIDTH_BARREL = 1.6f;
    static constexpr float TEX_SCALE_HEIGHT_BARREL = 1.6f;
    static constexpr float BARREL_BODY_WIDTH = 14;
    static constexpr float BARREL_BODY_HEIGHT = 18;

public:

    static Entity create(SDL_Texture* tex, int x, int y) {
        Entity barrel = Entity::create();

        Position position{x, y};

        b2BodyDef barrelBodyDef = b2DefaultBodyDef();
        barrelBodyDef.type = b2_dynamicBody;
        barrelBodyDef.position = {position.x / Game::BOX_SCALE, position.y / Game::BOX_SCALE};
        b2BodyId barrelBody = b2CreateBody(Game::boxWorld, &barrelBodyDef);

        b2ShapeDef padShapeDef = b2DefaultShapeDef();
        padShapeDef.density = 1;

        b2Polygon padBox = b2MakeBox(BARREL_BODY_WIDTH / Game::BOX_SCALE / 2, BARREL_BODY_HEIGHT / Game::BOX_SCALE / 2);
        b2CreatePolygonShape(barrelBody, &padShapeDef, &padBox);

        barrel.add<Position>(position);
        barrel.add<Drawable>(
            {
                tex,
                SDL_FRect{245, 70, 14, 18},
                TEX_SCALE_WIDTH_BARREL,
                TEX_SCALE_HEIGHT_BARREL,
                true
                });
        barrel.add<Moveable>({5,0});
        barrel.add<Body>({barrelBody});
        barrel.add<BarrelMove>({true, false, 2.0f, 1});

        return barrel;
    }
};

} // donkeykong

#endif //BARREL_H
