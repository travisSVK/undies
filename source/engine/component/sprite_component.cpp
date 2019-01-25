#include "sprite_component.hpp"
#include "SFML/Graphics/Texture.hpp"

void SpriteComponent::set_sprite(std::string _sprite_path)
{
    sf::Texture texture;
    if (!texture.loadFromFile(_sprite_path))
    {
        // fail...
    }

    _sprite.setTexture(texture);
}

const sf::Sprite &SpriteComponent::get_sprite()
{
    return _sprite;
}