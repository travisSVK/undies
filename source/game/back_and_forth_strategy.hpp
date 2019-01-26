#pragma once

#include "i_movement_strategy.hpp"
#include <SFML/Graphics.hpp>

class BackAndForthStrategy : public IMovementStrategy
{
public:
    // just leave the direction as it is without any movement speed
    void update_movement(Enemy::Direction &move_dir, int &target_x, int &target_y) override;
};