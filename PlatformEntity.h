#ifndef PLATFORMENTITY_H
#define PLATFORMENTITY_H
#include "bagel.h"
#include "Components.h"
#include <box2d/box2d.h>

using namespace bagel;

namespace donkeykong {

    class PlatformEntity : NoInstance {
    public:
        static Entity createPlatform(b2WorldId worldId, int centerX, int centerY, int width, int thickness = 10, float boxScale = 10.0f) {
            Entity platform = Entity::create();

            platform.add<Position>({centerX, centerY});

            b2BodyDef platformBodyDef = b2DefaultBodyDef();
            platformBodyDef.type = b2_staticBody;
            platformBodyDef.position = {centerX / boxScale, centerY / boxScale};
            b2BodyId platformBody = b2CreateBody(worldId, &platformBodyDef);

            b2ShapeDef platformShapeDef = b2DefaultShapeDef();
            platformShapeDef.density = 0;

            b2Polygon platformBox = b2MakeBox(width / boxScale / 2, thickness / boxScale / 2);
            b2CreatePolygonShape(platformBody, &platformShapeDef, &platformBox);

            platform.add<Body>({platformBody});

            return platform;
        }
    };

} // donkeykong

#endif //PLATFORMENTITY_H