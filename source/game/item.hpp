#pragma once

#include "entity.hpp"
#include "player.hpp"


class Item : public Entity
{

public:
	Item(const std::string sprite_name, int grid_x, int grid_y);
	void attach_player_entity(Player *player);
protected:

	void start() override;


	void update(float delta_time) override;
	bool is_player_touching();

private:

	Player *_player;
	int _grid_x;
	int _grid_y;
	//bool picked_up = false;
};
