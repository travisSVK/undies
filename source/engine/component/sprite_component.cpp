#include "sprite_component.hpp"

void SpriteComponent::set_sprite(const std::string &_sprite_path)
{
    if (!_texture.loadFromFile(_sprite_path))
    {
        // fail...
    }

    _sprite.setTexture(_texture);
}

sf::Vector2f SpriteComponent::get_sprite_scale() const
{
    return _sprite.getScale();
}