//
// Created by Matan Moskovich on 19/05/2025.
//

#include "BarrelSpawnSystem.h"

#include <iostream>

#include "bagel.h"

using namespace bagel;

namespace donkeykong {

    void BarrelSpawnSystem::spawnBarrel() {
        //std::cout << "BarrelSpawnSystem spawnBarrel" << std::endl;
        BarrelEntity::create(_tex,400,120);
        --_barrelSpawnCount;
        std::cout << "BarrelSpawnSystem spawnBarrel" << std::endl;
    }


}
