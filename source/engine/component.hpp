#pragma once

#include "engine_api.hpp"

class Entity;

class ENGINE_API Component
{
public:

    Entity* get_entity();

private:

    Entity* _entity;
};

