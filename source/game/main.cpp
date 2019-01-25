#include "managers/entity_manager.hpp"
#include "managers/render_manager.hpp"
#include "managers/sound_manager.hpp"
#include "player.hpp"

#include <SFML/Graphics.hpp>

int main(int argc, char* argv)
{
    sf::RenderWindow win(sf::VideoMode(800, 600), "Undies");

    SoundManager* sound_manager = SoundManager::get();
    EntityManager* entity_manager = EntityManager::get();
    RenderManager* render_manager = RenderManager::get(); // = RenderManager::get();

    render_manager->start_up(&win);

    Entity* player = new Player();
    entity_manager->register_entity(player);
    SoundComponent* sound_component = sound_manager->load_sound_component(player, "data/Undies_main_theme_-_16-bit.wav", "mainsound");
    sound_manager->play_sound("mainsound");

    while (true)
    {
        entity_manager->handle_events(win);
        entity_manager->update(0.01f);

        win.clear();

        // Render all objects.
        render_manager->render();

        win.display();
    }

    render_manager->shut_down();
    sound_manager->shut_down();

    return 0;
}
