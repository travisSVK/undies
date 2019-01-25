#include "render_manager.hpp"
#include "../component/sprite_component.hpp"
#include "../component/component.hpp"
#include "../entity.hpp"

RenderManager* RenderManager::get()
{
    static RenderManager instance;
    return &instance;
}

void RenderManager::render()
{
    const sf::Vector2u windowSize = _main_window->getSize();
    // Render main window.
    for (auto sprite_component : _sprite_components)
    {
        _main_window->draw(sprite_component->_sprite);
    }
}

SpriteComponent *RenderManager::load_sprite_component(Entity *_entity, const std::string &_sprite_file)
{
    SpriteComponent *_sprite_component = new SpriteComponent();
    _sprite_component->set_sprite(_sprite_file);
    _sprite_component->add_entity(_entity);
    _entity->add_component(_sprite_component);

    _sprite_components.push_back(_sprite_component);
    return _sprite_component;
}

void RenderManager::start_up(sf::RenderWindow* win)
{
    _main_window = win;
}

void RenderManager::shut_down()
{
    for (auto sprite_component : _sprite_components)
    {
        delete sprite_component;
    }
    _sprite_components.clear();
}
