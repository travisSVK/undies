#pragma once

#include "entity.hpp"

class Player;
class IMovementStrategy;
class ICollisionDetection;

class Enemy : public Entity
{
public:

    enum class Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

public:
    Enemy(int target_x, int target_y, float move_speed);
    ~Enemy();

    void set_grid_position(int target_x, int target_y);
    void attach_player_entity(Player *player);
    void set_move_direction(Direction move_dir);
    void set_movement_strategy(IMovementStrategy *movement_strategy);
    void set_collision_strategy(ICollisionDetection *collision_detection);
    bool check_player_detection() const;
protected:

    void start() override;

    void update(float delta_time) override;

private:
    void update_movement();
    void update_fov();

private:

    Direction _move_dir;
    Player *_player;
    IMovementStrategy *_movement_strategy;
    ICollisionDetection *_collision_detection;
    int _target_x;
    int _target_y;
    float _move_speed;
    sf::Vector2f _fov_vector_u;
    sf::Vector2f _fov_vector_v;
    sf::ConvexShape _fov_shape;
};
