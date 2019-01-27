#include "left_circling_strategy.hpp"
#include "managers/level_manager.hpp"

void LeftCirclingStrategy::update_movement(Enemy::Direction &move_dir, int &target_x, int &target_y)
{
    switch (move_dir)
    {
    case Enemy::Direction::UP:
    {
        int x = target_x - 1;
        if (LevelManager::get()->is_walkable(x, target_y))
        {
            target_x = x;
            move_dir = Enemy::Direction::LEFT;
        }
        else
        {
            int y = target_y - 1;
            if (LevelManager::get()->is_walkable(target_x, y))
            {
                target_y = y;
            }
        }
        // else we just stand:)
        break;
    }
    case Enemy::Direction::DOWN:
    {
        int x = target_x + 1;
        if (LevelManager::get()->is_walkable(x, target_y))
        {
            target_x = x;
            move_dir = Enemy::Direction::RIGHT;
        }
        else
        {
            int y = target_y + 1;
            if (LevelManager::get()->is_walkable(target_x, y))
            {
                target_y = y;
            }
        }
        // else we just stand:)
        break;
    }
    case Enemy::Direction::LEFT:
    {
        int y = target_y + 1;
        if (LevelManager::get()->is_walkable(target_x, y))
        {
            target_y = y;
            move_dir = Enemy::Direction::DOWN;
        }
        else
        {
            int x = target_x - 1;
            if (LevelManager::get()->is_walkable(x, target_y))
            {
                target_x = x;
            }
        }
        // else we just stand:)
        break;
    }
    case Enemy::Direction::RIGHT:
    {
        int y = target_y - 1;
        if (LevelManager::get()->is_walkable(target_x, y))
        {
            target_y = y;
            move_dir = Enemy::Direction::UP;
        }
        else
        {
            int x = target_x + 1;
            if (LevelManager::get()->is_walkable(x, target_y))
            {
                target_x = x;
            }
        }
        // else we just stand:)
        break;
    }
    default:
        break;
    }
}