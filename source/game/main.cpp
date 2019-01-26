#include "managers/entity_manager.hpp"
#include "managers/render_manager.hpp"
#include "player.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

int main(int argc, char* argv)
{
    sf::RenderWindow win(sf::VideoMode(32 * 32, 32 * 32), "Undies");

    EntityManager* entity_manager = EntityManager::get();
    RenderManager* render_manager = RenderManager::get(); // = RenderManager::get();

    render_manager->start_up(&win);

    Entity* player = new Player();
    entity_manager->register_entity(player);

    sf::Clock clock;
    float delta_time = 0.0f;

    while (true)
    {
        entity_manager->handle_events(win);
        entity_manager->update(delta_time);

        win.clear();

        // Render all objects.
        render_manager->render();

        win.display();

        sf::Time time = clock.getElapsedTime();
        clock.restart();
        delta_time = time.asSeconds();
    }

    render_manager->shut_down();


    return 0;
}
