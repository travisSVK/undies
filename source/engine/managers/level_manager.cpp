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
    _tile_prototype.resize(9);
    std::ifstream file("data/sprites.txt");

    std::string line;
    while (std::getline(file, line))
    {
        int index;
        std::string filepath;
        int walkable;
        std::stringstream iss(line);

        iss >> index >> filepath >> walkable;

        _tile_prototype[index].walkable = static_cast<bool>(walkable);
        _tile_prototype[index].texture.loadFromFile(filepath);
    }

    for (int x = 0; x < MAX_X; ++x)
    {
        for (int y = 0; y < MAX_Y; ++y)
        {
            _level_tiles[x][y].sprite.setPosition(sf::Vector2f(x * tile_scaling(), y * tile_scaling()));
            _level_tiles[x][y].sprite.setTexture(_tile_prototype[0].texture);
        }
    }
}

void LevelManager::shut_down()
{
}

bool LevelManager::is_walkable(int x, int y)
{
    if (x >= MAX_X || x < 0)
    {
        return false;
    }

    if (y >= MAX_Y || y < 0)
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

    for (int y = 0; y < MAX_Y; ++y)
    {
        std::string line;
        std::getline(level, line);
        std::stringstream iss(line);
        for (int x = 0; x < MAX_X; ++x)
        {
            int index;
            iss >> index;
            _level_tiles[x][y].sprite.setTexture(_tile_prototype[index].texture);
            _level_tiles[x][y].walkable = _tile_prototype[index].walkable;
        }
    }

    level.close();
}

void LevelManager::render(sf::RenderWindow& win)
{
    for (int x = 0; x < MAX_X; ++x)
    {
        for (int y = 0; y < MAX_Y; ++y)
        {
            win.draw(_level_tiles[x][y].sprite);
        }
    }
}
