#include "enemy.hpp"
#include "managers/entity_manager.hpp"
#include "player.hpp"
#include "i_movement_strategy.hpp"
#include "managers/level_manager.hpp"
#include "component/sprite_component.hpp"
#include "component/fov_component.hpp"
#include "managers/render_manager.hpp"

#define PI 3.14159265

void Enemy::start()
{
    RenderManager::get()->load_fov_component(this);
}

void Enemy::update(float delta_time)
{
    float move_speed = 0.0f;
    update_movement(move_speed);
    update_fov();
    float scaling = LevelManager::get()->tile_scaling();
    switch (_move_dir)
    {
    case Direction::UP:
    {
        move(0.0f, -move_speed * delta_time);
        if (get_position().y < _target_y * scaling)
        {
            set_position(_target_x * scaling, _target_y * scaling);
        }
        break;
    }
    case Direction::DOWN:
    {
        move(0.0f, move_speed * delta_time);
        if (get_position().y > _target_y * scaling)
        {
            set_position(_target_x * scaling, _target_y * scaling);
        }
        break;
    }
    case Direction::LEFT:
    {
        move(-move_speed * delta_time, 0.0f);
        if (get_position().x < _target_x * scaling)
        {
            set_position(_target_x * scaling, _target_y * scaling);
        }
        break;
    }
    case Direction::RIGHT:
    {
        move(move_speed * delta_time, 0.0f);
        if (get_position().x > _target_x * scaling)
        {
            set_position(_target_x * scaling, _target_y * scaling);
        }
        break;
    }
    default:
        break;
    }
}

void Enemy::attach_player_entity(Player *player)
{
    if (player)
    {
        _player = player;
    }
}

void Enemy::set_fov(float fov)
{
    _fov_angle = fov;
    _fov_shape.setPointCount(3);
}

void Enemy::set_move_direction(Direction move_dir)
{
    _move_dir = move_dir;
}

void Enemy::set_movement_strategy(IMovementStrategy *movement_strategy)
{
    _movement_strategy = movement_strategy;
}

void Enemy::update_movement(float move_speed)
{
    _movement_strategy->update_movement(_move_dir, move_speed, _target_x, _target_y);
}

void Enemy::check_player_detection() const
{
    SpriteComponent* sprite_component = _player->get_component<SpriteComponent>();
    if (sprite_component)
    {
        sf::Vector2f sprite_scale = sprite_component->get_sprite_scale();
        // check if the player is intersecting the FOV
        sf::Vector2f player_position = _player->get_position();

        // Use SAT to detect polygon detections
    }
}

void Enemy::update_fov()
{
    // get the rotation from direction to half angle left and right
    switch (_move_dir)
    {
    case Direction::UP:
    {
        float y = _player->get_position().y - 1.0f;
        float x = _player->get_position().x;
        x = (x * cos(_fov_angle / 2.0f * PI / 180.0f)) + (y * sin(_fov_angle / 2.0f * PI / 180.0f));
        y = (-x * sin(_fov_angle / 2.0f * PI / 180.0f)) + (y * cos(_fov_angle / 2.0f * PI / 180.0f));
        _fov_vector_v = sf::Vector2f(x, y);

        y = _player->get_position().y - 1.0f;
        x = _player->get_position().x;
        x = (x * cos((360.0f - _fov_angle) / 2.0f * PI / 180.0f)) + (y * sin(360.0f - _fov_angle / 2.0f * PI / 180.0f));
        y = (-x * sin(360.0f - _fov_angle / 2.0f * PI / 180.0f)) + (y * cos(360.0f - _fov_angle / 2.0f * PI / 180.0f));
        _fov_vector_u = sf::Vector2f(x, y);
        break;
    }
    case Direction::DOWN:
    {
        float y = _player->get_position().y + 1.0f;
        float x = _player->get_position().x;
        x = (x * cos(_fov_angle / 2.0f * PI / 180.0f)) + (y * sin(_fov_angle / 2.0f * PI / 180.0f));
        y = (-x * sin(_fov_angle / 2.0f * PI / 180.0f)) + (y * cos(_fov_angle / 2.0f * PI / 180.0f));
        _fov_vector_v = sf::Vector2f(x, y);

        y = _player->get_position().y + 1.0f;
        x = _player->get_position().x;
        x = (x * cos((360.0f - _fov_angle) / 2.0f * PI / 180.0f)) + (y * sin(360.0f - _fov_angle / 2.0f * PI / 180.0f));
        y = (-x * sin(360.0f - _fov_angle / 2.0f * PI / 180.0f)) + (y * cos(360.0f - _fov_angle / 2.0f * PI / 180.0f));
        _fov_vector_u = sf::Vector2f(x, y);
        break;
    }
    case Direction::LEFT:
    {
        float y = _player->get_position().y ;
        float x = _player->get_position().x - 1.0f;
        x = (x * cos(_fov_angle / 2.0f * PI / 180.0f)) + (y * sin(_fov_angle / 2.0f * PI / 180.0f));
        y = (-x * sin(_fov_angle / 2.0f * PI / 180.0f)) + (y * cos(_fov_angle / 2.0f * PI / 180.0f));
        _fov_vector_v = sf::Vector2f(x, y);

        y = _player->get_position().y - 1.0f;
        x = _player->get_position().x;
        x = (x * cos((360.0f - _fov_angle) / 2.0f * PI / 180.0f)) + (y * sin(360.0f - _fov_angle / 2.0f * PI / 180.0f));
        y = (-x * sin(360.0f - _fov_angle / 2.0f * PI / 180.0f)) + (y * cos(360.0f - _fov_angle / 2.0f * PI / 180.0f));
        _fov_vector_u = sf::Vector2f(x, y);
        break;
    }
    case Direction::RIGHT:
    {
        float y = _player->get_position().y;
        float x = _player->get_position().x + 1.0f;
        x = (x * cos(_fov_angle / 2.0f * PI / 180.0f)) + (y * sin(_fov_angle / 2.0f * PI / 180.0f));
        y = (-x * sin(_fov_angle / 2.0f * PI / 180.0f)) + (y * cos(_fov_angle / 2.0f * PI / 180.0f));
        _fov_vector_v = sf::Vector2f(x, y);

        y = _player->get_position().y + 1.0f;
        x = _player->get_position().x;
        x = (x * cos((360.0f - _fov_angle) / 2.0f * PI / 180.0f)) + (y * sin(360.0f - _fov_angle / 2.0f * PI / 180.0f));
        y = (-x * sin(360.0f - _fov_angle / 2.0f * PI / 180.0f)) + (y * cos(360.0f - _fov_angle / 2.0f * PI / 180.0f));
        _fov_vector_u = sf::Vector2f(x, y);
        break;
    }
    default:
        break;
    }
    _fov_shape.setPoint(0, sf::Vector2f(_player->get_position().x, _player->get_position().y));
    _fov_shape.setPoint(1, _fov_vector_u);
    _fov_shape.setPoint(2, _fov_vector_v);
    FovComponent *fov_component = get_component<FovComponent>();
    fov_component->set_fov(_fov_shape);
}
