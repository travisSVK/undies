#include <SFML/Graphics.hpp>

int main(int argc, char* argv)
{
    sf::RenderWindow win(sf::VideoMode(800, 600), "Undies");

    while (true)
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                win.close();
            }
        }

        win.clear();

        win.display();
    }

    return 0;
}
