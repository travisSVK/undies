#include "item.hpp"
#include "managers/entity_manager.hpp"
#include "player.hpp"
#include "managers/level_manager.hpp"
#include "component/sprite_component.hpp"
#include "managers/render_manager.hpp"
#include "managers/sound_manager.hpp"
#include <string>

Item::Item(const std::string sprite_name, int grid_x, int grid_y)
	: Entity()
{
	//sprite
	SpriteComponent* sprite = RenderManager::get()->load_sprite_component(this, sprite_name);

	//position
	_grid_x = grid_x;
	_grid_y = grid_y;
	float scaling = LevelManager::get()->tile_scaling();
	//todo: set origin?
	set_position(_grid_x*scaling, _grid_y*scaling);
	//should be a one-time because it's not moving?
}



void Item::start()
{
	// add sprite component.
	//SpriteComponent* sprite = RenderManager::get()->load_sprite_component(this, "data/graphics/Sister1.png");

}
void Item::update(float delta_time)
{
	//todo: anim?
	if (is_player_touching())
	{
		SoundManager::get()->play_sound("pick_up");
		set_position(12413526, 346347); //kill it by throwing it out of the screen lol
		EntityManager::get()->deregister_entity(this);
		//todo: do the pickup stuff
	}
}

void Item::attach_player_entity(Player *player)
{
	if (player)
	{
		_player = player;
	}
}

bool Item::is_player_touching()
{
	sf::Vector2i player_pos = _player->get_grid_position();
	return ((player_pos.x == _grid_x) && (player_pos.y == _grid_y));
}
