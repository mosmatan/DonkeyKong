//
// Created by Matan Moskovich on 19/05/2025.
//

#include "BarrelEntity.h"
#include "DonkeyKongGame.h"

namespace donkeykong {

     Entity BarrelEntity::create(SDL_Texture* tex, int x, int y) {
             Entity barrel = Entity::create();

             Position position{x, y};

             b2BodyDef barrelBodyDef = b2DefaultBodyDef();
             barrelBodyDef.type = b2_dynamicBody;
             barrelBodyDef.position = {position.x / DonkeyKongGame::BOX_SCALE, position.y / DonkeyKongGame::BOX_SCALE};
             b2BodyId barrelBody = b2CreateBody(DonkeyKongGame::boxWorld, &barrelBodyDef);

             b2ShapeDef padShapeDef = b2DefaultShapeDef();
             padShapeDef.density = 1;

             b2Polygon padBox = b2MakeBox(BARREL_BODY_WIDTH / DonkeyKongGame::BOX_SCALE / 2, BARREL_BODY_HEIGHT / DonkeyKongGame::BOX_SCALE / 2);
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
             barrel.add<RespawnWhen>({true, false, 750, y, x});

             return barrel;
         }

}
