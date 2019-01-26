#pragma once

#include "i_collision_detection.hpp"

class SatCollisionDetection : public ICollisionDetection 
{
public:
    bool detect_collision(const std::vector<sf::Vector2f> &convexPolygonA, const std::vector<sf::Vector2f> &convexPolygonB);
};