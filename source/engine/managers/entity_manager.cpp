#include "entity_manager.hpp"
#include "../entity.hpp"

EntityManager* EntityManager::get()
{
    static EntityManager instance;
    return &instance;
}

void EntityManager::register_entity(Entity* entity)
{
    _entities.push_back(entity);
    entity->start();
}

void EntityManager::update(float delta_time)
{
    for (int i = 0; i < _entities.size(); ++i)
    {
        _entities[i]->update(delta_time);
    }
}
