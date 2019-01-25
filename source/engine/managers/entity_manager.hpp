#pragma once

#include "../engine_api.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

class Entity;

class ENGINE_API EntityManager
{
public:

    static EntityManager* get();

    void register_entity(Entity* entity);

    void update(float delta_time);

    void handle_events(sf::RenderWindow& win);

private:

    std::vector<Entity*> _entities;
};
