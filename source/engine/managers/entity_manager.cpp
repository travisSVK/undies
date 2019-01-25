#include "entity_manager.hpp"

EntityManager* EntityManager::get()
{
    static EntityManager instance;
    return &instance;
}

void EntityManager::register_entity(Entity* entity)
{

}

void EntityManager::update()
{
    for (int i = 0; i < _entities.size(); ++i)
    {

    }
}
