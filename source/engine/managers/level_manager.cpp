#include "level_manager.hpp"

#include <sstream>
#include <fstream>

LevelManager* LevelManager::get()
{
    static LevelManager instance;
    return &instance;
}

void LevelManager::start_up()
{
    _tile_prototype.resize(10);
    _tile_prototype[0].texture.loadFromFile("data/test.png");
    _tile_prototype[1].texture.loadFromFile("data/test.png");
    _tile_prototype[2].texture.loadFromFile("data/test.png");
    _tile_prototype[3].texture.loadFromFile("data/test.png");
    _tile_prototype[4].texture.loadFromFile("data/test.png");
    _tile_prototype[5].texture.loadFromFile("data/test.png");
    _tile_prototype[6].texture.loadFromFile("data/test.png");
    _tile_prototype[7].texture.loadFromFile("data/test.png");
    _tile_prototype[8].texture.loadFromFile("data/test.png");
    _tile_prototype[9].texture.loadFromFile("data/test.png");

    for (int x = 0; x < 32; ++x)
    {
        for (int y = 0; y < 32; ++y)
        {
            _level_tiles[x][y].sprite.setPosition(sf::Vector2f(x * 32, y * 32));
            _level_tiles[x][y].sprite.setTexture(_tile_prototype[0].texture);
        }
    }
}

void LevelManager::shut_down()
{
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

void LevelManager::load_level(const std::string& filename)
{
    std::ifstream level(filename);

    for (int x = 0; x < 32; ++x)
    {
        std::string line;
        std::getline(level, line);
        std::stringstream iss(line);
        for (int y = 0; y < 32; ++y)
        {
            int index;
            iss >> index;
            _level_tiles[x][y].sprite.setTexture(_tile_prototype[index].texture);
        }
    }
}

void LevelManager::render(sf::RenderWindow& win)
{
    for (int x = 0; x < 32; ++x)
    {
        for (int y = 0; y < 32; ++y)
        {
            win.draw(_level_tiles[x][y].sprite);
        }
    }
}
