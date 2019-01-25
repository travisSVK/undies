#pragma once

#include "../engine_api.hpp"

#include <vector>

class Entity;

class ENGINE_API EntityManager
{
public:

    EntityManager* get();

    void register_entity(Entity* entity);

    void update();

private:

    std::vector<Entity*> _entities;
};
