#include "entity.hpp"

Entity::Entity()
    : _position(0.0f, 0.0f)
    , _scale(1.0f, 1.0f)
{
}

Entity::~Entity()
{
}

void Entity::add_component(Component* component)
{
    _components.push_back(component);
}

sf::Vector2f Entity::get_position() const
{
    return _position;
}

sf::Vector2f Entity::get_scale() const
{
    return _scale;
}

void Entity::set_position(float x, float y)
{
    set_position(sf::Vector2f(x, y));
}

void Entity::set_position(const sf::Vector2f& position)
{
    _position = position;
}

void Entity::set_scale(float x, float y)
{
    set_scale(sf::Vector2f(x, y));
}

void Entity::set_scale(const sf::Vector2f& scale)
{
    _scale = scale;
}

void Entity::move(float x, float y)
{
    move(sf::Vector2f(x, y));
}

void Entity::move(const sf::Vector2f& position)
{
    _position += position;
}

void Entity::start()
{
}

void Entity::update(float delta_time)
{
}

void Entity::handle_events(sf::Event& e)
{
}
