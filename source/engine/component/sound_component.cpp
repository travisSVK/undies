#include "sound_component.hpp"

void SoundComponent::set_sound(const std::string &_sound_path)
{
    if (!_music.openFromFile(_sound_path))
    {
        // fail
    }
}