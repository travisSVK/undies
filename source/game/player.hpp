#pragma once

#include "entity.hpp"

class Player : public Entity
{
public:
	Player(int target_x, int target_y);

	void set_grid_position(int target_x, int target_y);

private:

    enum class Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

protected:

    void start() override;

    void update(float delta_time) override;

    void handle_events(sf::Event& e) override;

private:

    Direction _dir;
    bool _is_moving;
    int _target_x;
    int _target_y;
};
