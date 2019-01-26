#pragma once

#include "../engine_api.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

class FovComponent;
class SpriteComponent;
class Component;
class Entity;

class ENGINE_API RenderManager 
{
public:

    static RenderManager* get();

    void render();

    SpriteComponent *load_sprite_component(Entity *_entity, const std::string &_sprite_file);
    
    FovComponent *load_fov_component(Entity *_entity);

    void deregister_fov_component(FovComponent* fov);

    void deregister_sprite_component(SpriteComponent* sprite);

    void start_up(sf::RenderWindow* win);

    void shut_down();

private:
    RenderManager() = default;
    ~RenderManager() = default;

    RenderManager(RenderManager const&) = delete;
    void operator=(RenderManager const&) = delete;
    sf::RenderWindow *_main_window;
    std::vector<SpriteComponent*> _sprite_components;
    std::vector<FovComponent*> _fov_components;
};
