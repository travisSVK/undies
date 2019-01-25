#include "sound_manager.hpp"
#include "../component/sound_component.hpp"
#include "../component/component.hpp"
#include "../entity.hpp"

SoundManager* SoundManager::get()
{
    static SoundManager instance;
    return &instance;
}

SoundComponent *SoundManager::load_sound_component(Entity *_entity, const std::string &_sound_file, const std::string &_sound_type)
{
    SoundComponent *_sound_component = new SoundComponent();
    _sound_component->set_sound(_sound_file);
    _sound_component->add_entity(_entity);
    _entity->add_component(_sound_component);

    _sound_components[_sound_type] = _sound_component;
    return _sound_component;
}

void SoundManager::start_up()
{
    // TODO
}

void SoundManager::play_sound(const std::string &_sound_type)
{
    _sound_components[_sound_type]->_music.play();
}

void SoundManager::shut_down()
{
    for (auto sound_component : _sound_components_vec)
    {
        sound_component->_music.stop();
        delete sound_component;
    }
    _sound_components.clear();
    _sound_components_vec.clear();
}
