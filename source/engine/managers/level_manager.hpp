#pragma once

#include "../engine_api.hpp"

class ENGINE_API LevelManager
{
public:

    struct LevelTile
    {
        bool walkable = true;
    };

public:

    static LevelManager* get();

    bool is_walkable(int x, int y);

    float tile_scaling();

private:

    LevelTile _level_tiles[32][32];
};
