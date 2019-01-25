#pragma once
#include "../engine_api.hpp"
#include "GLM/glm.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class SpriteComponent;

class ENGINE_API RenderManager 
{
    /// Render world containing entities.
    /**
     * @param world Contains a bunch of entities.
     * @param targetDisplay Display type to render.
     * @param soundSources Whether to show sound sources.
     * @param particleEmitters Whether to show particle emitters.
     * @param lightSources Whether to show light sources.
     * @param cameras Whether to show cameras.
     * @param physics Whether to show physics volumes.
     * @param camera Camera through which to render (or first camera in the world if nullptr).
     * @param lighting Whether to light the scene (otherwise full ambient is used).
     * @param lightVolumes Whether to show light culling volumes.
     */
    void Render();

private:
    RenderManager();
    ~RenderManager();
    RenderManager(RenderManager const&) = delete;
    void operator=(RenderManager const&) = delete;
    sf::RenderWindow *_main_window;
    std::vector<SpriteComponent *> _sprite_components;
};

