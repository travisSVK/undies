#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class ICollisionDetection 
{
public:
    virtual ~ICollisionDetection() = default;
    virtual bool detect_collision(const std::vector<sf::Vector2f> &convexPolygonA, const std::vector<sf::Vector2f> &convexPolygonB) = 0;
};