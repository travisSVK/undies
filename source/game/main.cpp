#include "managers/entity_manager.hpp"

#include <SFML/Graphics.hpp>

int main(int argc, char* argv)
{
    sf::RenderWindow win(sf::VideoMode(800, 600), "Undies");

    EntityManager* entity_manager = EntityManager::get();

    while (true)
    {
        entity_manager->handle_events(win);
        entity_manager->update(0.01f);

        win.clear();

        win.display();
    }

    return 0;
}
