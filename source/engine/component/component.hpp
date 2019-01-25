#pragma once

class Entity;

class Component
{
public:

    Entity* get_entity();

private:

    Entity* _entity;
};

