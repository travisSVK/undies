#include "player.hpp"
#include "managers/render_manager.hpp"
#include "managers/level_manager.hpp"

void Player::start()
{
    // add sprite component.
    SpriteComponent* sprite = RenderManager::get()->load_sprite_component(this, "data/ugly_face.png");
    
    _is_moving = false;
    _dir = Direction::UP;
}

void Player::update(float delta_time)
{
    if (_is_moving)
    {
        float scaling = LevelManager::get()->tile_scaling();
        switch (_dir)
        {
        case Direction::UP:
        {
            move(0.0f, -10.0f * delta_time);
            if (get_position().y < _target_y * scaling)
            {
                set_position(_target_x * scaling, _target_y * scaling);
                _is_moving = false;
            }
            break;
        }
        case Direction::DOWN:
        {
            move(0.0f, 10.0f * delta_time);
            if (get_position().y > _target_y * scaling)
            {
                set_position(_target_x * scaling, _target_y * scaling);
                _is_moving = false;
            }
            break;
        }
        case Direction::LEFT:
        {
            move(-10.0f * delta_time, 0.0f);
            if (get_position().x < _target_x * scaling)
            {
                set_position(_target_x * scaling, _target_y * scaling);
                _is_moving = false;
            }
            break;
        }
        case Direction::RIGHT:
        {
            move(10.0f * delta_time, 0.0f);
            if (get_position().x > _target_x * scaling)
            {
                set_position(_target_x * scaling, _target_y * scaling);
                _is_moving = false;
            }
            break;
        }
        default:
            break;
        }
    }
}

void Player::handle_events(sf::Event& e)
{
    if (_is_moving)
    {
        return;
    }

    switch (e.type)
    {
    case sf::Event::KeyPressed:
    {
        if (e.key.code == sf::Keyboard::Up)
        {
            int y = _target_y + 1;
            if (LevelManager::get()->is_walkable(_target_x, y))
            {
                _target_y = y;
                _is_moving = true;
                _dir = Direction::UP;
            }
        }
        else if (e.key.code == sf::Keyboard::Down)
        {
            int y = _target_y - 1;
            if (LevelManager::get()->is_walkable(_target_x, y))
            {
                _target_y = y;
                _is_moving = true;
                _dir = Direction::DOWN;
            }
        }
        else if (e.key.code == sf::Keyboard::Left)
        {
            int x = _target_x - 1;
            if (LevelManager::get()->is_walkable(x, _target_y))
            {
                _target_x = x;
                _is_moving = true;
                _dir = Direction::LEFT;
            }
        }
        else if (e.key.code == sf::Keyboard::Right)
        {
            int x = _target_x + 1;
            if (LevelManager::get()->is_walkable(x, _target_y))
            {
                _target_x = x;
                _is_moving = true;
                _dir = Direction::RIGHT;
            }
        }

        break;
    }
    default:
        break;
    }
}
