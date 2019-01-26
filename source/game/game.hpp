#pragma once

#include "entity.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "back_and_forth_strategy.hpp"
#include "sat_collision_detection.hpp"
#include "standing_strategy.hpp"
#include "managers/render_manager.hpp"
#include "managers/entity_manager.hpp"
#include "managers/sound_manager.hpp"
#include "managers/level_manager.hpp"

class Game : public Entity
{
private:

    enum class GameState
    {
        MENU,
        MENU_TO_GAME,
        GAME,
        GAME_TO_GAME_OVER,
        GAME_OVER,
        GAME_OVER_TO_MENU
    };

public:

    Game();

    ~Game();

protected:

    void start() override;

    void update(float delta_time) override;

    void handle_events(sf::Event& e) override;

private:

    void menu(float delta_time);

    void menu(sf::Event& e);

    void menu_to_game();

    void game(float delta_time);

    void game(sf::Event& e);

    void game_to_game_over();

private:

    GameState _game_state;

    Player* _player;
    Entity* _left_player;
    Entity* _right_player;
    Entity* _background;
    Enemy* _enemy;

    bool _left_selected;
    bool _left_down;
    bool _right_down;
    float _left_scale;
    float _right_scale;
};
