#pragma once

#include "entity.hpp"

class Player : public Entity
{
public:

protected:

    void start() override;

    void update(float delta_time) override;

    void handle_events(sf::Event e) override;
};
