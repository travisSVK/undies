#include "player.hpp"
#include "managers/render_manager.hpp"
#include "managers/level_manager.hpp"

Player::Player(int target_x, int target_y)
	: Entity()
{
    set_origin(16.0f, 16.0f);
	set_grid_position(target_x, target_y);
}

sf::Vector2i Player::get_grid_position()
{
	//honestly this is misusing target x/y. but whatever
	return sf::Vector2<int>(_target_x, _target_y);
}

void Player::set_grid_position(int target_x, int target_y)
{
	//set both target and position to the arguments
	//may bug out if used while moving? idk
	_target_x = target_x;
	_target_y = target_y;
	float scaling = LevelManager::get()->tile_scaling();
	set_position(_target_x*scaling+16, _target_y*scaling+16);
}


void Player::start()
{
    // add sprite component.
    SpriteComponent* sprite = RenderManager::get()->load_sprite_component(this, "data/graphics/Sister1.png");
    
    _is_moving = false;
    _dir = Direction::UP;
}

void Player::update(float delta_time)
{
    float speed = 128.0f;

    if (_is_moving)
    {
        float scaling = LevelManager::get()->tile_scaling();
        switch (_dir)
        {
        case Direction::UP:
        {
            move(0.0f, -speed * delta_time);
            if (get_position().y < (_target_y * scaling) + 16.0f)
            {
                set_position((_target_x * scaling) + 16.0f, (_target_y * scaling) + 16.0f);
				_is_moving = false;
            }
            break;
        }
        case Direction::DOWN:
        {
            move(0.0f, speed * delta_time);
            if (get_position().y > (_target_y * scaling) + 16.0f)
            {
                set_position((_target_x * scaling) + 16.0f, (_target_y * scaling) + 16.0f);
                _is_moving = false;
            }
            break;
        }
        case Direction::LEFT:
        {
            move(-speed * delta_time, 0.0f);
            if (get_position().x < (_target_x * scaling) + 16.0f)
            {
                set_position((_target_x * scaling) + 16.0f, (_target_y * scaling) + 16.0f);
                _is_moving = false;
            }
            break;
        }
        case Direction::RIGHT:
        {
            move(speed * delta_time, 0.0f);
            if (get_position().x > (_target_x * scaling) + 16.0f)
            {
                set_position((_target_x * scaling) + 16.0f, (_target_y * scaling) + 16.0f);
                _is_moving = false;
            }
            break;
        }
        default:
            break;
        }
	} 
	else
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			int y = _target_y - 1;
			if (LevelManager::get()->is_walkable(_target_x, y))
			{
				_target_y = y;
				set_rotation(0.0f);
				_is_moving = true;
				_dir = Direction::UP;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			int y = _target_y + 1;
			if (LevelManager::get()->is_walkable(_target_x, y))
			{
				set_rotation(180.0f);
				_target_y = y;
				_is_moving = true;
				_dir = Direction::DOWN;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			int x = _target_x - 1;
			if (LevelManager::get()->is_walkable(x, _target_y))
			{
				set_rotation(270.0f);
				_target_x = x;
				_is_moving = true;
				_dir = Direction::LEFT;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			int x = _target_x + 1;
			if (LevelManager::get()->is_walkable(x, _target_y))
			{
				set_rotation(90.0f);
				_target_x = x;
				_is_moving = true;
				_dir = Direction::RIGHT;
			}
		}
	}
}

void Player::handle_events(sf::Event& e)
{
    // moved movement code to update instead
}
