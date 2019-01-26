#include "game.hpp"

Game::Game()
    : _game_state(GameState::MENU)
    , _left_player(nullptr)
    , _right_player(nullptr)
    , _left_selected(false)
    , _left_down(false)
    , _right_down(false)
    , _left_scale(0.0f)
    , _right_scale(0.0f)
{
}

Game::~Game()
{
}

void Game::start()
{
    _game_state = GameState::MENU;

    _left_player = new Entity();
    _right_player = new Entity();

    _left_selected = true;
    _left_down = true;
    _right_down = false;

    _left_scale = 3.5f;
    _right_scale = 3.0f;

    _background = new Entity();
    RenderManager::get()->load_sprite_component(_background, "data/graphics/Background.png");
    _background->set_origin(16.0f, 16.0f);
    _background->set_scale(1000000.0f, 100000.0f);
    _background->set_position((LevelManager::get()->MAX_X / 2) * 32, (LevelManager::get()->MAX_Y / 2) * 32);

    RenderManager::get()->load_sprite_component(_left_player, "data/graphics/Brother1.png");
    _left_player->set_origin(16.0f, 16.0f);
    _left_player->set_scale(_left_scale, _left_scale);
    _left_player->set_position((LevelManager::get()->MAX_X / 4) * 32, (LevelManager::get()->MAX_Y - 4) * 32);

    RenderManager::get()->load_sprite_component(_right_player, "data/graphics/Sister1.png");
    _right_player->set_origin(16.0f, 16.0f);
    _right_player->set_scale(_right_scale, _right_scale);
    _right_player->set_position((LevelManager::get()->MAX_X / 4) * 3 * 32, (LevelManager::get()->MAX_Y - 4) * 32);
}

void Game::update(float delta_time)
{
    switch (_game_state)
    {
    case Game::GameState::MENU:
        menu(delta_time);
        break;
    case Game::GameState::MENU_TO_GAME:
        menu_to_game();
        break;
    case Game::GameState::GAME:
        game(delta_time);
        break;
    case Game::GameState::GAME_TO_GAME_OVER:
        game_to_game_over();
        break;
    case Game::GameState::GAME_OVER:
        game_to_game_over();
        break;
    case Game::GameState::GAME_OVER_TO_MENU:
        game_to_game_over();
        break;
    default:
        break;
    }
}

void Game::handle_events(sf::Event& e)
{
    switch (_game_state)
    {
    case Game::GameState::MENU:
        menu(e);
        break;
    case Game::GameState::MENU_TO_GAME:
        break;
    case Game::GameState::GAME:
        game(e);
        break;
    case Game::GameState::GAME_TO_GAME_OVER:
        game_to_game_over();
        break;
    case Game::GameState::GAME_OVER:
        break;
    case Game::GameState::GAME_OVER_TO_MENU:
        break;
    default:
        break;
    }
}

void Game::menu(float delta_time)
{
    if (_left_selected)
    {
        if (_left_down)
        {
            _left_scale -= delta_time * 3.0f;
            if (_left_scale < 3.0f)
            {
                _left_scale = 3.0f;
                _left_down = false;
            }
        }
        else
        {
            _left_scale += delta_time * 3.0f;
            if (_left_scale > 3.5f)
            {
                _left_scale = 3.5f;
                _left_down = true;
            }
        }

        _right_scale = 3.0f;
    }
    else
    {
        if (_right_down)
        {
            _right_scale -= delta_time * 3.0f;
            if (_right_scale < 3.0f)
            {
                _left_scale = 3.0f;
                _right_down = false;
            }
        }
        else
        {
            _right_scale += delta_time * 3.0f;
            if (_right_scale > 3.5f)
            {
                _right_scale = 3.5f;
                _right_down = true;
            }
        }

        _left_scale = 3.0f;
    }

    _left_player->set_scale(_left_scale, _left_scale);
    _right_player->set_scale(_right_scale, _right_scale);
}

void Game::menu(sf::Event& e)
{
    if (e.type == sf::Event::KeyPressed)
    {
        if (e.key.code == sf::Keyboard::Left)
        {
            _left_selected = true;
        }
        else if (e.key.code == sf::Keyboard::Right)
        {
            _left_selected = false;
        }
        else if (e.key.code == sf::Keyboard::Enter)
        {
            _game_state = GameState::MENU_TO_GAME;
        }
    }
}

void Game::menu_to_game()
{
    EntityManager* entity_manager = EntityManager::get();
    SoundManager* sound_manager = SoundManager::get();
    LevelManager* level_manager = LevelManager::get();

    _left_player->set_enabled(false);
    _right_player->set_enabled(false);

    _player = new Player(2, 13);
    entity_manager->register_entity(_player);
    SoundComponent* sound_component = sound_manager->load_sound_component(_player, "data/Undies_main_theme_-_16-bit.wav", "mainsound");
    sound_manager->play_sound("mainsound");

    if (_left_selected)
    {
        RenderManager::get()->load_sprite_component(_player, "data/graphics/Brother1.png");
    }
    else
    {
        RenderManager::get()->load_sprite_component(_player, "data/graphics/Sister1.png");
    }

    _background->set_enabled(false);

    _enemy = new Enemy(12, 12, 128.0f);
    EntityManager::get()->register_entity(_enemy);
    
    _enemy->attach_player_entity(_player);
    _enemy->set_move_direction(Enemy::Direction::UP);

    BackAndForthStrategy* str = new BackAndForthStrategy();
    _enemy->set_movement_strategy(str);
    
    SatCollisionDetection* sat = new SatCollisionDetection();
    _enemy->set_collision_strategy(sat);

    level_manager->load_level("data/level_test.txt");

    _game_state = GameState::GAME;
}

void Game::game(float delta_time)
{
    bool collision = _enemy->check_player_detection();
    if (collision)
    {
        _game_state = GameState::GAME_TO_GAME_OVER;
    }
}

void Game::game(sf::Event & e)
{
}

void Game::game_to_game_over()
{
    _game_state = GameState::MENU;
}
