#include "entity.hpp"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::add_component(Component* component)
{
    _components.push_back(component);
}

void Entity::start()
{
}

void Entity::update(float delta_time)
{
}

void Entity::handle_events(sf::Event e)
{
}
