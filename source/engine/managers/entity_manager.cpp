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

void EntityManager::handle_events(sf::RenderWindow& win)
{
    sf::Event event;
    while (win.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            win.close();
        }

        for (int i = 0; i < _entities.size(); ++i)
        {
            _entities[i]->handle_events(event);
        }
    }
}
