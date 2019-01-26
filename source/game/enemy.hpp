#pragma once

#include "entity.hpp"

class Player;
class IMovementStrategy;

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
    void attach_player_entity(Player *player);
    void set_fov(float fov);
    void set_move_direction(Direction move_dir);
    void set_movement_strategy(IMovementStrategy *movement_strategy);
    void check_player_detection() const;
protected:

    void start() override;

    void update(float delta_time) override;

private:
    void update_movement(float move_speed);
    void update_fov();

private:

    Direction _move_dir;
    Player *_player;
    float _fov_angle;
    IMovementStrategy *_movement_strategy;
    int _target_x;
    int _target_y;
    sf::Vector2f _fov_vector_u;
    sf::Vector2f _fov_vector_v;
    sf::ConvexShape _fov_shape;
};
