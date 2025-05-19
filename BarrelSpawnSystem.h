//
// Created by Matan Moskovich on 19/05/2025.
//

#ifndef BARRELSPAWNSYSTEM_H
#define BARRELSPAWNSYSTEM_H
#include "bagel.h"
#include "BarrelEntity.h"

using namespace bagel;

namespace donkeykong {

class BarrelSpawnSystem {

    SDL_Texture* _tex;
    int _barrelSpawnCount;
    float _timeToSpawn = 0.0f;
    const float _spawnInterval = 1.0f; // Time interval between barrel spawns

public:

    BarrelSpawnSystem(SDL_Texture* tex, int barrels_count = 5, float spawn_interval = 1.0f)
        : _tex(tex),
        _barrelSpawnCount(barrels_count),
        _spawnInterval(spawn_interval) {
    }

    void setTexture(SDL_Texture* tex) {
        _tex = tex;
    }

    void spawnBarrel();

    void update(float deltaTime) {

        if (_barrelSpawnCount <= 0)
            return;

        _timeToSpawn += deltaTime;
        if (_timeToSpawn >= _spawnInterval) {
            spawnBarrel();
            _timeToSpawn = 0.0f;
        }
    }
};

} // donkeykong

#endif //BARRELSPAWNSYSTEM_H
