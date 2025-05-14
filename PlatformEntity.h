//
// Created by Matan Moskovich on 14/05/2025.
//

#ifndef PLATFORMENTITY_H
#define PLATFORMENTITY_H
#include "bagel.h"
#include "Components.h"
#include <box2d/box2d.h>

using namespace bagel;

namespace donkeykong {

    class PlatformEntity : NoInstance {
    public:
        static Entity createPlatform(b2WorldId worldId, int x, int y, int width, int height, float boxScale = 10.0f) {
            Entity platform = Entity::create();
            platform.add<Position>({x, y});
            b2BodyDef platformBodyDef = b2DefaultBodyDef();
            platformBodyDef.type = b2_staticBody;
            platformBodyDef.position = {x / boxScale, y / boxScale};
            b2BodyId platformBody = b2CreateBody(worldId, &platformBodyDef);
            b2ShapeDef platformShapeDef = b2DefaultShapeDef();
            platformShapeDef.density = 0; // Static bodies don't need density
            //platformShapeDef.friction = 0.3f; // Removed this line
            b2Polygon platformBox = b2MakeBox(width / boxScale / 2, height / boxScale / 2);
            b2CreatePolygonShape(platformBody, &platformShapeDef, &platformBox);

            platform.add<Body>({platformBody});

            return platform;
        }
    };

} // donkeykong

#endif //PLATFORMENTITY_H