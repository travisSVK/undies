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
    SoundManager::get()->load_sound_component(this, "data/music/main_theme.wav", "main_theme");
    SoundManager::get()->load_sound_component(this, "data/music/menu.wav", "menu");
    SoundManager::get()->load_sound_component(this, "data/music/pick_up.wav", "menu_option");

    SoundManager::get()->play_sound("menu");

    _game_state = GameState::MENU;

    _is_finished = false;

    _left_player = new Entity();
    _right_player = new Entity();

    _left_selected = true;
    _left_down = true;
    _right_down = false;

    _end_selected = false;

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
    case Game::GameState::GAME_OVER_TO_MENU:
        game_to_game_over();
        break;
    case Game::GameState::GAME_OVER:
        game_over(delta_time);
        break;
    case Game::GameState::EXIT:
        exit();
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
    case Game::GameState::GAME:
        game(e);
        break;
    case Game::GameState::GAME_OVER:
        game_over(e);
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
        if (e.key.code == sf::Keyboard::Left && !_left_selected)
        {
            SoundManager::get()->stop_sound("menu_option");
            SoundManager::get()->play_sound("menu_option");
            _left_selected = true;
        }
        else if (e.key.code == sf::Keyboard::Right && _left_selected)
        {
            SoundManager::get()->stop_sound("menu_option");
            SoundManager::get()->play_sound("menu_option");
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

    SoundManager::get()->stop_sound("menu");
    SoundManager::get()->play_sound("main_theme");

    _left_player->set_enabled(false);
    _right_player->set_enabled(false);

    _player = new Player(2, 13);
    entity_manager->register_entity(_player);

    if (_left_selected)
    {
        RenderManager::get()->load_sprite_component(_player, "data/graphics/Brother1.png");
    }
    else
    {
        RenderManager::get()->load_sprite_component(_player, "data/graphics/Sister1.png");
    }
    _background->set_enabled(false);

    Enemy *enemy = new Enemy(12, 12, 128.0f);
    EntityManager::get()->register_entity(enemy);
    
    enemy->attach_player_entity(_player);
    enemy->set_move_direction(Enemy::Direction::UP);

    BackAndForthStrategy* str = new BackAndForthStrategy();
    enemy->set_movement_strategy(str);
    
    SatCollisionDetection* sat = new SatCollisionDetection();
    enemy->set_collision_strategy(sat);
    _enemies.push_back(enemy);

    level_manager->load_level("data/level_test.txt");

    _game_state = GameState::GAME;
}

void Game::game(float delta_time)
{
    for (auto enemy : _enemies)
    {
        bool collision = enemy->check_player_detection();
        if (collision)
        {
            _game_state = GameState::GAME_TO_GAME_OVER;
        }
    }
    
}

void Game::game(sf::Event & e)
{
}

void Game::game_to_game_over()
{
    for (auto enemy : _enemies)
    {
        EntityManager::get()->deregister_entity(enemy);
        delete enemy;
    }
    _enemies.clear();
    EntityManager::get()->deregister_entity(_player);
    delete _player;

    _left_player->set_enabled(true);
    _right_player->set_enabled(true);
    _background->set_enabled(true);
    _left_down = true;
    _right_down = false;
    _game_state = GameState::GAME_OVER;
    SoundManager::get()->play_sound("menu");
    SoundManager::get()->stop_sound("main_theme");
}

void Game::game_over(float delta_time)
{
    if (!_end_selected)
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

void Game::game_over(sf::Event& e)
{
    if (e.type == sf::Event::KeyPressed)
    {
        if (e.key.code == sf::Keyboard::Left)
        {
            _end_selected = false;
        }
        else if (e.key.code == sf::Keyboard::Right)
        {
            _end_selected = true;
        }
        else if (e.key.code == sf::Keyboard::Enter)
        {
            if (_end_selected)
            {
                _game_state = GameState::EXIT;
            }
            else
            {
                _game_state = GameState::MENU_TO_GAME;
            }
        }
    }
}

void Game::exit()
{
    EntityManager::get()->deregister_entity(_left_player);
    EntityManager::get()->deregister_entity(_right_player);
    EntityManager::get()->deregister_entity(_background);
    delete _left_player;
    delete _right_player;
    delete _background;

    _is_finished = true;
}

bool Game::is_finished()
{
    return _is_finished;
}