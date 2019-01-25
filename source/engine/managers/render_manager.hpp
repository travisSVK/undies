#pragma once

#include "../engine_api.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class SpriteComponent;
class Component;
class Entity;

class ENGINE_API RenderManager 
{
public:
    void render();
    SpriteComponent *load_sprite_component(Entity *_entity, const std::string &_sprite_file);

private:
    RenderManager();
    ~RenderManager();
    RenderManager(RenderManager const&) = delete;
    void operator=(RenderManager const&) = delete;
    sf::RenderWindow *_main_window;
    std::vector<SpriteComponent *> _sprite_components;
};

