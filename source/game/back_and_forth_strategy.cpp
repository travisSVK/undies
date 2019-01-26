#include "back_and_forth_strategy.hpp"
#include "managers/level_manager.hpp"

void BackAndForthStrategy::update_movement(Enemy::Direction &move_dir, float &move_speed, int target_x, int target_y)
{
    move_speed = 128.0f;
    switch (move_dir)
    {
    case Enemy::Direction::UP:
    {
        int y = target_y - 1;
        if (LevelManager::get()->is_walkable(target_x, y))
        {
            target_y = y;
            move_dir = Enemy::Direction::UP;
        }
        else
        {
            int y = target_y + 1;
            if (LevelManager::get()->is_walkable(target_x, y))
            {
                target_y = y;
                move_dir = Enemy::Direction::DOWN;
            }
        }
        // else we just stand:)
        break;
    }
    case Enemy::Direction::DOWN:
    {
        int y = target_y + 1;
        if (LevelManager::get()->is_walkable(target_x, y))
        {
            target_y = y;
            move_dir = Enemy::Direction::DOWN;
        }
        else
        {
            int y = target_y - 1;
            if (LevelManager::get()->is_walkable(target_x, y))
            {
                target_y = y;
                move_dir = Enemy::Direction::UP;
            }
        }
        // else we just stand:)
        break;
    }
    case Enemy::Direction::LEFT:
    {
        int x = target_x - 1;
        if (LevelManager::get()->is_walkable(x, target_y))
        {
            target_x = x;
            move_dir = Enemy::Direction::LEFT;
        }
        else
        {
            int x = target_x + 1;
            if (LevelManager::get()->is_walkable(x, target_y))
            {
                target_x = x;
                move_dir = Enemy::Direction::RIGHT;
            }
        }
        // else we just stand:)
        break;
    }
    case Enemy::Direction::RIGHT:
    {
        int x = target_x + 1;
        if (LevelManager::get()->is_walkable(x, target_y))
        {
            target_x = x;
            move_dir = Enemy::Direction::RIGHT;
        }
        else
        {
            int x = target_x - 1;
            if (LevelManager::get()->is_walkable(x, target_y))
            {
                target_x = x;
                move_dir = Enemy::Direction::LEFT;
            }
        }
        // else we just stand:)
        break;
    }
    default:
        break;
    }
}