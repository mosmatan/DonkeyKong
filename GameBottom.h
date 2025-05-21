//
// Created by Matan Moskovich on 21/05/2025.
//

#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H
#include "bagel.h"

using namespace bagel;


class GameBottom {

public:

    static Entity create(int y) {

        Entity bottom = Entity::create();

        bottom.add<Position>({0, y});
        bottom.add<CollosionDetector>({0, 3000,10});
        bottom.add<BottomComponent>({});


        return bottom;
    }

};



#endif //GAMEBUTTON_H
