#include "fov_component.hpp"
#include "../managers/render_manager.hpp"

void FovComponent::set_fov(const sf::ConvexShape &fov_shape)
{
    _fov_shape = fov_shape;
    _fov_shape.setFillColor(sf::Color(255, 255, 200, 25));
}

FovComponent::~FovComponent()
{
    RenderManager::get()->deregister_fov_component(this);
}
