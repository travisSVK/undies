#pragma once

#include "component.hpp"
#include "engine_api.hpp"

#include <vector>

class ENGINE_API Entity
{
public:

    template <typename C>
    Component* get_component();

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
