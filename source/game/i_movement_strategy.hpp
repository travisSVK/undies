#pragma once
#include "enemy.hpp"

class IMovementStrategy 
{
public:
    virtual ~IMovementStrategy() = default;
    virtual void update_movement(Enemy::Direction &move_dir, float &move_speed, int target_x, int target_y) = 0;

private:
    // TODO place collision grid here
};