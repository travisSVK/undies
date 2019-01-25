#include "player.hpp"
#include "managers/render_manager.hpp"

void Player::start()
{
    // add sprite component.
    SpriteComponent* sprite = RenderManager::get()->load_sprite_component(this, "data/ugly_face.png");
}

void Player::update(float delta_time)
{
    move(_move_dir);
}

void Player::handle_events(sf::Event& e)
{
    _move_dir = sf::Vector2f(0.0f, 0.0f);

    switch (e.type)
    {
    case sf::Event::KeyPressed:
    {
        if (e.key.code == sf::Keyboard::Up)
        {
            _move_dir = sf::Vector2f(0.0f, 10.0f);
        }
        else if (e.key.code == sf::Keyboard::Down)
        {
            _move_dir = sf::Vector2f(0.0f, -10.0f);
        }
        else if (e.key.code == sf::Keyboard::Left)
        {
            _move_dir = sf::Vector2f(-10.0f, 0.0f);
        }
        else if (e.key.code == sf::Keyboard::Right)
        {
            _move_dir = sf::Vector2f(10.0f, 0.0f);
        }

        break;
    }
    default:
        break;
    }
}
