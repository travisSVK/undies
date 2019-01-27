#pragma once
#include "../engine_api.hpp"
#include "component.hpp"
#include "SFML/Graphics.hpp"
#include "../managers/render_manager.hpp"
#include "../engine_api.hpp"

class ENGINE_API SpriteComponent : public Component
{
    friend RenderManager;

public:

    ~SpriteComponent();
    void set_sprite(const std::string &_sprite_path);

private:

    SpriteComponent() = default;
    SpriteComponent(SpriteComponent const&) = delete;
    void operator=(SpriteComponent const&) = delete;

    sf::Sprite _sprite;
    sf::Texture _texture;
};
