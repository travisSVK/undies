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
    SoundManager::get()->load_sound_component(this, "data/music/caught.wav", "caught");
    SoundManager::get()->load_sound_component(this, "data/music/level_complete.wav", "level_complete");

    SoundManager::get()->play_sound("menu", true);

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
    _level_num = 1;

    //_final_state.x = 

    _background = new Entity();
    RenderManager::get()->load_sprite_component(_background, "data/graphics/Background.png");
    _background->set_origin(16.0f, 16.0f);
    _background->set_scale(1000000.0f, 100000.0f);
    _background->set_position((LevelManager::get()->MAX_X / 2) * 32, (LevelManager::get()->MAX_Y / 2) * 32);

    RenderManager::get()->load_sprite_component(_left_player, "data/graphics/Brother1.png");
    _left_player->set_origin(16.0f, 16.0f);
    _left_player->set_scale(_left_scale, _left_scale);
    _left_player->set_position((LevelManager::get()->MAX_X / 4) * 32, (LevelManager::get()->MAX_Y - 4) * 32);

    _logo = new Entity();
    RenderManager::get()->load_sprite_component(_logo, "data/graphics/logo.png");
    _logo->set_scale(1.2f, 1.2f);
    _logo->set_origin(256 / 2, 256 / 2);
    _logo->set_position((LevelManager::get()->MAX_X * 32) / 2, 100.0f);

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
    case Game::GameState::LEVEL_FINISHED_TO_MENU:
        level_finished_to_menu();
        break;
    case Game::GameState::MENU_TO_NEW_LEVEL:
        menu_to_new_level(delta_time);
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
    case Game::GameState::MENU_TO_NEW_LEVEL:
        menu_to_new_level(e);
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
            SoundManager::get()->stop_sound("menu");
            _player = new Player(2, 13);
            EntityManager::get()->register_entity(_player);
            if (_left_selected)
            {
                RenderManager::get()->load_sprite_component(_player, "data/graphics/Brother1.png");
            }
            else
            {
                RenderManager::get()->load_sprite_component(_player, "data/graphics/Sister1.png");
            }
        }
    }
}

void Game::menu_to_game()
{
    EntityManager* entity_manager = EntityManager::get();
    SoundManager* sound_manager = SoundManager::get();
    LevelManager* level_manager = LevelManager::get();

    SoundManager::get()->play_sound("main_theme", true);
    _left_player->set_enabled(false);
    _right_player->set_enabled(false);
    _logo->set_enabled(false);
    _background->set_enabled(false);
    _player->set_enabled(true);

    switch (_level_num)
    {
    case 1:
        load_level_01();
        break;
    case 2:
        load_level_02();
        break;
    case 3:
        load_level_03();
        break;
    case 4:
        load_level_04();
        break;
    case 5:
        load_level_05();
        break;
    case 6:
        load_level_06();
        break;
    case 7:
        load_level_07();
        break;
    case 8:
        load_level_08();
        break;
    case 9:
        load_level_09();
        break;
    case 10:
        load_level_10();
        break;
    default:
        break;
    }

    //load_level_01();

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
            _player->set_enabled(false);
        }
    }

    float scaling = LevelManager::get()->tile_scaling();
    if (LevelManager::get()->is_final((_player->get_position().x - 16) / scaling, (_player->get_position().y - 16) / scaling))
    {
        _player->set_enabled(false);
        _game_state = GameState::LEVEL_FINISHED_TO_MENU;
    }
}

void Game::game(sf::Event & e)
{
}

void Game::game_to_game_over()
{
    deload_level();


	RenderManager *render_manager = RenderManager::get();

	//render_manager->deregister_sprite_component(_background->get_component<SpriteComponent>());
	_background->remove_component<SpriteComponent>();
	_left_player->remove_component<SpriteComponent>();
	_right_player->remove_component<SpriteComponent>();
	render_manager->load_sprite_component(_background, "data/graphics/retry.png");
	_background->set_origin(256.0f, 256.0f);
	_background->set_scale(1.0f, 1.0f);
	_background->set_position((LevelManager::get()->MAX_X / 2) * 32, (LevelManager::get()->MAX_Y / 2) * 32);

	render_manager->load_sprite_component(_left_player, "data/graphics/yes.png");
	_left_player->set_origin(16.0f, 16.0f);
	_left_player->set_scale(_left_scale, _left_scale);
	_left_player->set_position((LevelManager::get()->MAX_X / 4) * 32, (LevelManager::get()->MAX_Y - 4) * 32);

	render_manager->load_sprite_component(_right_player, "data/graphics/no.png");
	_right_player->set_origin(16.0f, 16.0f);
	_right_player->set_scale(_right_scale, _right_scale);
	_right_player->set_position((LevelManager::get()->MAX_X / 4) * 3 * 32, (LevelManager::get()->MAX_Y - 4) * 32);

    _left_player->set_enabled(true);
    _right_player->set_enabled(true);
    _background->set_enabled(true);
    _left_down = true;
    _right_down = false;
    _game_state = GameState::GAME_OVER;
    SoundManager::get()->stop_sound("main_theme");
    SoundManager::get()->play_sound("caught", true);
}

void Game::level_finished_to_menu()
{
    deload_level();


	RenderManager *render_manager = RenderManager::get();

	//render_manager->deregister_sprite_component(_background->get_component<SpriteComponent>());
	//delete the spirtes to replace texture
	_background->remove_component<SpriteComponent>();
	_left_player->remove_component<SpriteComponent>();
	_right_player->remove_component<SpriteComponent>();

	switch (_level_num)
	{
	case 1:
		render_manager->load_sprite_component(_background, "data/graphics/stage2.png");
		break;
	case 2:
		render_manager->load_sprite_component(_background, "data/graphics/stage3.png");
		break;
	case 3:
		render_manager->load_sprite_component(_background, "data/graphics/stage4.png");
		break;
	case 4:
		render_manager->load_sprite_component(_background, "data/graphics/stage5.png");
		break;
	case 5:
		render_manager->load_sprite_component(_background, "data/graphics/stage6.png");
		break;
	case 6:
		render_manager->load_sprite_component(_background, "data/graphics/stage7.png");
		break;
	case 7:
		render_manager->load_sprite_component(_background, "data/graphics/stage8.png");
		break;
	case 8:
		render_manager->load_sprite_component(_background, "data/graphics/stage9.png");
		break;
	case 9:
		render_manager->load_sprite_component(_background, "data/graphics/stage10.png");
		break;
	default:
		break;
	}
	_background->set_origin(512.0f, 512.0f);
	_background->set_scale(1.0f, 0.6f);
	_background->set_position((LevelManager::get()->MAX_X / 2) * 32, (LevelManager::get()->MAX_Y / 2) * 32 - 64);


	render_manager->load_sprite_component(_left_player, "data/graphics/letsgo.png");
	_left_player->set_origin(16.0f, 16.0f);
	_left_player->set_scale(_left_scale, _left_scale);
	_left_player->set_position((LevelManager::get()->MAX_X / 4) * 32, (LevelManager::get()->MAX_Y - 4) * 32);

	render_manager->load_sprite_component(_right_player, "data/graphics/giveup.png");
	_right_player->set_origin(16.0f, 16.0f);
	_right_player->set_scale(_right_scale, _right_scale);
	_right_player->set_position((LevelManager::get()->MAX_X / 4) * 3 * 32, (LevelManager::get()->MAX_Y - 4) * 32);

    _left_player->set_enabled(true);
    _right_player->set_enabled(true);
    _background->set_enabled(true);
    _left_down = true;
    _right_down = false;
    _game_state = GameState::MENU_TO_NEW_LEVEL;
    SoundManager::get()->stop_sound("main_theme");
    SoundManager::get()->play_sound("level_complete", true);
}

void Game::menu_to_new_level(float delta_time)
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

void Game::menu_to_new_level(sf::Event& e)
{
    if (e.type == sf::Event::KeyPressed)
    {
        if (e.key.code == sf::Keyboard::Left && _end_selected)
        {
            SoundManager::get()->stop_sound("menu_option");
            SoundManager::get()->play_sound("menu_option");
            _end_selected = false;
        }
        else if (e.key.code == sf::Keyboard::Right && !_end_selected)
        {
            SoundManager::get()->stop_sound("menu_option");
            SoundManager::get()->play_sound("menu_option");
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
                SoundManager::get()->stop_sound("level_complete");
                deload_level();
                ++_level_num;

                _game_state = GameState::MENU_TO_GAME;
            }
        }
    }
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
        if (e.key.code == sf::Keyboard::Left && _end_selected)
        {
            SoundManager::get()->stop_sound("menu_option");
            SoundManager::get()->play_sound("menu_option");
            _end_selected = false;
        }
        else if (e.key.code == sf::Keyboard::Right && !_end_selected)
        {
            SoundManager::get()->stop_sound("menu_option");
            SoundManager::get()->play_sound("menu_option");
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
                SoundManager::get()->stop_sound("caught");
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
    EntityManager::get()->deregister_entity(_player);
    delete _left_player;
    delete _right_player;
    delete _background;
    delete _player;

    _is_finished = true;
}

void Game::deload_level()
{
    for (auto e : _enemies)
    {
        EntityManager::get()->deregister_entity(e);
        delete e;
    }

    _enemies.clear();
}

void Game::load_level_01()
{
    _player->set_grid_position(2, 13);
    {
        Enemy *enemy = new Enemy(12, 8, 128.0f);
        EntityManager::get()->register_entity(enemy);
        enemy->attach_player_entity(_player);
        enemy->set_move_direction(Enemy::Direction::RIGHT);
        BackAndForthStrategy* str1 = new BackAndForthStrategy();
        enemy->set_movement_strategy(str1);
        SatCollisionDetection* sat1 = new SatCollisionDetection();
        enemy->set_collision_strategy(sat1);
        _enemies.push_back(enemy);
    }

    LevelManager::get()->load_level("data/level_01.txt");
}

void Game::load_level_02()
{
    _player->set_grid_position(2, 13);
    {
        Enemy *enemy = new Enemy(12, 8, 128.0f);
        EntityManager::get()->register_entity(enemy);
        enemy->attach_player_entity(_player);
        enemy->set_move_direction(Enemy::Direction::RIGHT);
        BackAndForthStrategy* str1 = new BackAndForthStrategy();
        enemy->set_movement_strategy(str1);
        SatCollisionDetection* sat1 = new SatCollisionDetection();
        enemy->set_collision_strategy(sat1);
        _enemies.push_back(enemy);
    }
    LevelManager::get()->load_level("data/level_02.txt");
}

void Game::load_level_03()
{
    _player->set_grid_position(2, 13);
    LevelManager::get()->load_level("data/level_03.txt");
}

void Game::load_level_04()
{
    _player->set_grid_position(2, 13);
    LevelManager::get()->load_level("data/level_04.txt");
}

void Game::load_level_05()
{
    _player->set_grid_position(2, 13);
    {
        Enemy *enemy = new Enemy(8, 12, 128.0f);
        EntityManager::get()->register_entity(enemy);
        enemy->attach_player_entity(_player);
        enemy->set_move_direction(Enemy::Direction::UP);
        BackAndForthStrategy* str1 = new BackAndForthStrategy();
        enemy->set_movement_strategy(str1);
        SatCollisionDetection* sat1 = new SatCollisionDetection();
        enemy->set_collision_strategy(sat1);
        _enemies.push_back(enemy);
    }

    {
        Enemy *enemy = new Enemy(13, 8, 128.0f);
        EntityManager::get()->register_entity(enemy);
        enemy->attach_player_entity(_player);
        enemy->set_move_direction(Enemy::Direction::RIGHT);
        BackAndForthStrategy* str2 = new BackAndForthStrategy();
        enemy->set_movement_strategy(str2);
        SatCollisionDetection* sat2 = new SatCollisionDetection();
        enemy->set_collision_strategy(sat2);
        _enemies.push_back(enemy);
    }

    {
        Enemy *enemy = new Enemy(13, 1, 128.0f);
        EntityManager::get()->register_entity(enemy);
        enemy->attach_player_entity(_player);
        enemy->set_move_direction(Enemy::Direction::LEFT);
        BackAndForthStrategy* str = new BackAndForthStrategy();
        enemy->set_movement_strategy(str);
        SatCollisionDetection* sat = new SatCollisionDetection();
        enemy->set_collision_strategy(sat);
        _enemies.push_back(enemy);
    }

    {
        Enemy *enemy = new Enemy(13, 6, 128.0f);
        EntityManager::get()->register_entity(enemy);
        enemy->attach_player_entity(_player);
        enemy->set_move_direction(Enemy::Direction::UP);
        BackAndForthStrategy* str = new BackAndForthStrategy();
        enemy->set_movement_strategy(str);
        SatCollisionDetection* sat = new SatCollisionDetection();
        enemy->set_collision_strategy(sat);
        _enemies.push_back(enemy);
    }

    LevelManager::get()->load_level("data/level_05.txt");
}

void Game::load_level_06()
{
    LevelManager::get()->load_level("data/level_06.txt");
}

void Game::load_level_07()
{
    LevelManager::get()->load_level("data/level_07.txt");
}

void Game::load_level_08()
{
    LevelManager::get()->load_level("data/level_08.txt");
}

void Game::load_level_09()
{
    LevelManager::get()->load_level("data/level_09.txt");
}

void Game::load_level_10()
{
    LevelManager::get()->load_level("data/level_10.txt");
}

bool Game::is_finished()
{
    return _is_finished;
}
