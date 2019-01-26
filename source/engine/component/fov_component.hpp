#pragma once
#include "component.hpp"
#include "SFML/Graphics.hpp"
#include "../managers/render_manager.hpp"
#include "../engine_api.hpp"

class ENGINE_API FovComponent : public Component
{
    friend RenderManager;

public:

    void set_fov(const sf::ConvexShape &fov_shape);

private:

    FovComponent() = default;
    ~FovComponent();
    FovComponent(FovComponent const&) = delete;
    void operator=(FovComponent const&) = delete;

    sf::ConvexShape _fov_shape;
};
