#pragma once

#include "component/component.hpp"
#include "engine_api.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

class ENGINE_API Entity
{
private:

    friend class EntityManager;

public:

    Entity();

    virtual ~Entity();

    void add_component(Component* component);

    template <typename C>
    Component* get_component();

    sf::Vector2f get_position() const;

    sf::Vector2f get_scale() const;

    void set_position(float x, float y);

    void set_position(const sf::Vector2f& position);

    void set_scale(float x, float y);

    void set_scale(const sf::Vector2f& scale);

    void move(float x, float y);

    void move(const sf::Vector2f& position);

protected:

    virtual void start();

    virtual void update(float delta_time);

    virtual void handle_events(sf::Event& e);

private:

    std::vector<Component*> _components;

    sf::Vector2f _position;

    sf::Vector2f _scale;
};

template<typename C>
Component* Entity::get_component()
{
    for (int i = 0; i < _components.size(); ++i)
    {
        Component* comp = dynamic_cast<C*>(_components[i]);
        if (comp)
        {
            return comp;
        }
    }
}
