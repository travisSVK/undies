#include "component.hpp"

Entity* Component::get_entity()
{
    return _entity;
}

void Component::add_entity(Entity *_set_entity)
{
    _entity = _set_entity;
}
