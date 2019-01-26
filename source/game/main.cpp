#include "managers/entity_manager.hpp"
#include "managers/render_manager.hpp"
#include "managers/sound_manager.hpp"
#include "managers/level_manager.hpp"
#include "standing_strategy.hpp"
#include "back_and_forth_strategy.hpp"
#include "sat_collision_detection.hpp"
#include "player.hpp"
#include "enemy.hpp"

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
    level_manager->load_level("data/level_test.txt");

    Player* player = new Player(2, 13);
    entity_manager->register_entity(player);
    SoundComponent* sound_component = sound_manager->load_sound_component(player, "data/Undies_main_theme_-_16-bit.wav", "mainsound");
    sound_manager->play_sound("mainsound");

    sf::Clock clock;
    float delta_time = 0.0f;

    Enemy* enemy = new Enemy(12, 12, 100.0f);
    entity_manager->register_entity(enemy);

    enemy->attach_player_entity(player);
    enemy->set_move_direction(Enemy::Direction::UP);
    BackAndForthStrategy* str = new BackAndForthStrategy();
    enemy->set_movement_strategy(str);
    SatCollisionDetection* sat = new SatCollisionDetection();
    enemy->set_collision_strategy(sat);

    while (win.isOpen())
    {
        entity_manager->handle_events(win);
        entity_manager->update(delta_time);

        win.clear();

        level_manager->render(win);

        // Render all objects.
        render_manager->render();

        // TEST collision
        bool collision = enemy->check_player_detection();
        if (collision)
        {
            break;
        }

        win.display();

        sf::Time time = clock.getElapsedTime();
        clock.restart();
        delta_time = time.asSeconds();
    }

    level_manager->shut_down();
    render_manager->shut_down();
    sound_manager->shut_down();

    return 0;
}
