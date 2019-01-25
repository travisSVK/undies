#pragma once
#include "component.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "../managers/render_manager.hpp"

class SpriteComponent : public Component
{
    friend RenderManager;
public:
    void set_sprite(std::string _sprite_path);
    const sf::Sprite &get_sprite();

private:
    SpriteComponent();
    ~SpriteComponent();
    SpriteComponent(SpriteComponent const&) = delete;
    void operator=(SpriteComponent const&) = delete;

    sf::Sprite _sprite;
};