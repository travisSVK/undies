#include "level_manager.hpp"

LevelManager* LevelManager::get()
{
    static LevelManager instance;
    return &instance;
}

bool LevelManager::is_walkable(int x, int y)
{
    if (x >= 32 || x < 0)
    {
        return false;
    }

    if (y >= 32 || y < 0)
    {
        return false;
    }

    return _level_tiles[x][y].walkable;
}

float LevelManager::tile_scaling()
{
    return 32.0f;
}
