#pragma once

#include "entity.hpp"

class Player : public Entity
{
protected:

    void start() override;

    void update(float delta_time) override;

    void handle_events(sf::Event& e) override;

private:

    sf::Vector2f _move_dir;
};
