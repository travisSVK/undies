#pragma once
#include "../engine_api.hpp"

#include "../engine_api.hpp"

class Entity;

class ENGINE_API Component
{
public:

    Entity* get_entity();
    void add_entity(Entity *_set_entity);
    virtual ~Component() = default;

private:

    Entity* _entity;
};

