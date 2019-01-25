#pragma once

class Entity;

class Component
{
public:

    Entity* get_entity();
    void add_entity(Entity *_set_entity);
    virtual ~Component() = default;

private:

    Entity* _entity;
};

