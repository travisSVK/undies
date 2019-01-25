#pragma once

#include "component.hpp"
#include "engine_api.hpp"

#include <SFML/Window.hpp>
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

protected:

    virtual void start();

    virtual void update(float delta_time);

    virtual void handle_events(sf::Event e);

private:

    std::vector<Component*> _components;
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
