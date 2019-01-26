#include "enemy.hpp"
#include "managers/entity_manager.hpp"
#include "player.hpp"
#include "i_movement_strategy.hpp"
#include "managers/level_manager.hpp"
#include "component/sprite_component.hpp"
#include "component/fov_component.hpp"
#include "managers/render_manager.hpp"
#include "i_collision_detection.hpp"

#define PI 3.14159265

Enemy::Enemy(int target_x, int target_y, float move_speed) : Entity()
{
    _move_speed = move_speed;
    set_origin(16.0f, 16.0f);
    _fov_shape.setPointCount(3);
    set_grid_position(target_x, target_y);
}

Enemy::~Enemy()
{
    delete _movement_strategy;
    delete _collision_detection;

    Entity::~Entity();
}

void Enemy::set_grid_position(int target_x, int target_y)
{
    _target_x = target_x;
    _target_y = target_y;
    float scaling = LevelManager::get()->tile_scaling();
    set_position(_target_x*scaling + 16, _target_y*scaling + 16);
}

void Enemy::start()
{
    RenderManager::get()->load_fov_component(this);
    RenderManager::get()->load_sprite_component(this, "data/graphics/Father1.png");
}

void Enemy::update(float delta_time)
{
    float scaling = LevelManager::get()->tile_scaling();
    switch (_move_dir)
    {
    case Direction::UP:
    {
        move(0.0f, -_move_speed * delta_time);
        if (get_position().y < (_target_y * scaling + 16))
        {
            set_position(_target_x * scaling + 16.0f, _target_y * scaling + 16.0f);
            update_movement();
        }
        break;
    }
    case Direction::DOWN:
    {
        move(0.0f, _move_speed * delta_time);
        if (get_position().y > (_target_y * scaling + 16))
        {
            set_position(_target_x * scaling + 16.0f, _target_y * scaling + 16.0f);
            update_movement();
        }
        break;
    }
    case Direction::LEFT:
    {
        move(-_move_speed * delta_time, 0.0f);
        if (get_position().x < _target_x * scaling + 16)
        {
            set_position(_target_x * scaling + 16.0f, _target_y * scaling + 16.0f);
            update_movement();
        }
        break;
    }
    case Direction::RIGHT:
    {
        move(_move_speed * delta_time, 0.0f);
        if (get_position().x > _target_x * scaling + 16)
        {
            set_position(_target_x * scaling + 16.0f, _target_y * scaling + 16.0f);
            update_movement();
        }
        break;
    }
    default:
        break;
    }
    update_fov();
}

void Enemy::attach_player_entity(Player *player)
{
    if (player)
    {
        _player = player;
    }
}

void Enemy::set_move_direction(Direction move_dir)
{
    _move_dir = move_dir;
    switch (_move_dir)
    {
    case Direction::UP:
    {
        _target_y -= 1;
        break;
    }
    case Direction::DOWN:
    {
        _target_y += 1;
        break;
    }
    case Direction::LEFT:
    {
        _target_x -= 1;
        break;
    }
    case Direction::RIGHT:
    {
        _target_x += 1;
        break;
    }
    default:
        break;
    }
}

void Enemy::set_movement_strategy(IMovementStrategy *movement_strategy)
{
    _movement_strategy = movement_strategy;
}

void Enemy::set_collision_strategy(ICollisionDetection *collision_detection)
{
    _collision_detection = collision_detection;
}

void Enemy::update_movement()
{
    _movement_strategy->update_movement(_move_dir, _target_x, _target_y);
}

bool Enemy::check_player_detection() const
{
    SpriteComponent* sprite_component = _player->get_component<SpriteComponent>();
    if (sprite_component)
    {
        // check if the player is intersecting the FOV
        sf::Vector2f player_position = _player->get_position();

        // Use SAT to detect polygon detections
        bool collision = _collision_detection->detect_collision(
            std::vector<sf::Vector2f>{get_position(), _fov_vector_u, _fov_vector_v},
            std::vector<sf::Vector2f>{
            sf::Vector2f(player_position.x + 16.0f, player_position.y + 16.0f),
                sf::Vector2f(player_position.x - 16.0f, player_position.y + 16.0f),
                sf::Vector2f(player_position.x - 16.0f, player_position.y - 16.0f),
                sf::Vector2f(player_position.x + 16.0f, player_position.y - 16.0f)});

        if (collision)
        {
            return true;
        }
    }
    return false;
}

void Enemy::update_fov()
{
    // get the rotation from direction to half angle left and right
    switch (_move_dir)
    {
    case Direction::UP:
    {
        _fov_vector_v = sf::Vector2f(get_position().x + 15, get_position().y - 100);
        _fov_vector_u = sf::Vector2f(get_position().x - 15, get_position().y - 100);
        break;
    }
    case Direction::DOWN:
    {
        _fov_vector_v = sf::Vector2f(get_position().x - 15, get_position().y + 100);
        _fov_vector_u = sf::Vector2f(get_position().x + 15, get_position().y + 100);
        break;
    }
    case Direction::LEFT:
    {
        _fov_vector_v = sf::Vector2f(get_position().x - 100, get_position().y + 15);
        _fov_vector_u = sf::Vector2f(get_position().x - 100, get_position().y - 15);
        break;
    }
    case Direction::RIGHT:
    {
        _fov_vector_v = sf::Vector2f(get_position().x + 100, get_position().y - 15);
        _fov_vector_u = sf::Vector2f(get_position().x + 100, get_position().y + 15);
        break;
    }
    default:
        break;
    }
    _fov_shape.setPoint(0, sf::Vector2f(get_position().x, get_position().y));
    _fov_shape.setPoint(1, _fov_vector_u);
    _fov_shape.setPoint(2, _fov_vector_v);
    FovComponent *fov_component = get_component<FovComponent>();
    fov_component->set_fov(_fov_shape);
}
