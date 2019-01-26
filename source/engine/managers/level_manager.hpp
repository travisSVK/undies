#pragma once

#include "../engine_api.hpp"

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class ENGINE_API LevelManager final
{
public:

    struct LevelTile
    {
        sf::Sprite sprite;
        bool walkable = true;
    };

    struct TilePrototype
    {
        sf::Texture texture;
        bool walkable = true;
    };

public:

    static LevelManager* get();

    void start_up();

    void shut_down();

    bool is_walkable(int x, int y);

    float tile_scaling();

    void load_level(const std::string& filename);

    void render(sf::RenderWindow& win);

private:

    LevelTile _level_tiles[32][32];

    std::vector<TilePrototype> _tile_prototype;

	const int MAX_X = 24;
	const int MAX_Y = 15;
};
