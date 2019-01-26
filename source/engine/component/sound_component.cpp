#include "sound_component.hpp"
#include "../managers/sound_manager.hpp"

void SoundComponent::set_sound(const std::string &_sound_path)
{
    if (!_music.openFromFile(_sound_path))
    {
        // fail
    }
}

SoundComponent::~SoundComponent()
{
    SoundManager::get()->deregister_sound_component(this);
}
