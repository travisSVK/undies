#include "render_manager.hpp"
#include "../component/sprite_component.hpp"

RenderManager::~RenderManager()
{
    for (auto sprite_component : _sprite_components)
    {
        delete sprite_component;
    }
    _sprite_components.clear();
}

void RenderManager::render()
{
    const sf::Vector2u windowSize = _main_window->getSize();

    if (_main_window->isOpen && windowSize.x > 0 && windowSize.y > 0) {
        // Render main window.
        for (auto sprite_component : _sprite_components)
        {
            _main_window->draw(sprite_component->get_sprite());
        }
    }
}
