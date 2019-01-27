#include "managers/entity_manager.hpp"
#include "managers/render_manager.hpp"
#include "managers/sound_manager.hpp"
#include "managers/level_manager.hpp"
#include "standing_strategy.hpp"
#include "back_and_forth_strategy.hpp"
#include "sat_collision_detection.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "game.hpp"
#include "item.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

int main(int argc, char* argv)
{
    SoundManager* sound_manager = SoundManager::get();
    EntityManager* entity_manager = EntityManager::get();
    RenderManager* render_manager = RenderManager::get(); // = RenderManager::get();
    LevelManager* level_manager = LevelManager::get();

    sf::RenderWindow win(sf::VideoMode(level_manager->MAX_X * 32, level_manager->MAX_Y * 32), "Undies");

    render_manager->start_up(&win);
    level_manager->start_up();
    
    Game* game = new Game();
    entity_manager->register_entity(game);

    //level_manager->load_level("data/level_test.txt");

    /*Player* player = new Player(2, 13);
    entity_manager->register_entity(player);*/

 //   Item* item_test = new Item("data/graphics/Sister1.png", 3, 13);
 //  item_test->attach_player_entity(player);
 // entity_manager->register_entity(item_test);
	//sound_manager->load_sound_component(item_test, "data/sfx/pick_up.wav", "pick_up");

	// SoundComponent* sound_component = sound_manager->load_sound_component(player, "data/Undies_main_theme_-_16-bit.wav", "mainsound");
    //sound_manager->play_sound("mainsound");

    sf::Clock clock;
    float delta_time = 0.0f;

    while (win.isOpen())
    {
        entity_manager->handle_events(win);
        entity_manager->update(delta_time);
        
        win.clear();

        level_manager->render(win);

        // Render all objects.
        render_manager->render();

        win.display();

        sf::Time time = clock.getElapsedTime();
        clock.restart();
        delta_time = time.asSeconds();

        if (game->is_finished())
        {
            break;
        }
    }

    level_manager->shut_down();
    render_manager->shut_down();
    sound_manager->shut_down();

    return 0;
}
