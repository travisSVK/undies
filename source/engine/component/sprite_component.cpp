#include "sprite_component.hpp"
#include "../managers/render_manager.hpp"

void SpriteComponent::set_sprite(const std::string &_sprite_path)
{
    if (!_texture.loadFromFile(_sprite_path))
    {
        // fail...
    }

    _sprite.setTexture(_texture);
}

SpriteComponent::~SpriteComponent()
{
    RenderManager::get()->deregister_sprite_component(this);
}
