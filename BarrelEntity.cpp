//
// Created by Matan Moskovich on 19/05/2025.
//

#include "BarrelEntity.h"
#include "Game.h"

namespace donkeykong {

     Entity BarrelEntity::create(SDL_Texture* tex, int x, int y) {

         BarrelEntity::BARREL_ANIMATION = new Drawable*[2] {
             new Drawable[4] { // SPINING
                 {tex,SDL_FRect{245, 70, 14, 18},TEX_SCALE_WIDTH_BARREL,TEX_SCALE_HEIGHT_BARREL,true,},
                 {tex,SDL_FRect{261, 70, 14, 18},TEX_SCALE_WIDTH_BARREL,TEX_SCALE_HEIGHT_BARREL,true,},
                 {tex,SDL_FRect{277, 70, 14, 18},TEX_SCALE_WIDTH_BARREL,TEX_SCALE_HEIGHT_BARREL,true,},
                 {tex,SDL_FRect{293, 70, 14, 18},TEX_SCALE_WIDTH_BARREL,TEX_SCALE_HEIGHT_BARREL,true,},
             },
             new Drawable[4] { // FALLING
                 {tex,SDL_FRect{245, 55, 14, 12},TEX_SCALE_WIDTH_BARREL,TEX_SCALE_HEIGHT_BARREL,true,},
                 {tex,SDL_FRect{245, 55, 14, 12},TEX_SCALE_WIDTH_BARREL,TEX_SCALE_HEIGHT_BARREL,true,},
                 {tex,SDL_FRect{245, 55, 14, 12},TEX_SCALE_WIDTH_BARREL,TEX_SCALE_HEIGHT_BARREL,true,},
                 {tex,SDL_FRect{245, 55, 14, 12},TEX_SCALE_WIDTH_BARREL,TEX_SCALE_HEIGHT_BARREL,true,},
             },
         };


         Entity barrel = Entity::create();

         Position position{x, y};

         b2BodyDef barrelBodyDef = b2DefaultBodyDef();
         barrelBodyDef.type = b2_dynamicBody;
         barrelBodyDef.position = {position.x / Game::BOX_SCALE, position.y / Game::BOX_SCALE};
         b2BodyId barrelBody = b2CreateBody(Game::boxWorld, &barrelBodyDef);

         b2ShapeDef barrelShapeDef = b2DefaultShapeDef();
         barrelShapeDef.density = 1;

         b2Polygon barrelBox = b2MakeBox(BARREL_BODY_WIDTH / Game::BOX_SCALE / 2, BARREL_BODY_HEIGHT / Game::BOX_SCALE / 2);
         b2CreatePolygonShape(barrelBody, &barrelShapeDef, &barrelBox);

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
         barrel.add<CollosionDetector>({0, BARREL_BODY_WIDTH, BARREL_BODY_HEIGHT/3});
            barrel.add<Animation>({BARREL_ANIMATION, 2, 4, 0, 0, Animation::type::BARREL});

         return barrel;
     }

}
