#pragma once
#include "component.hpp"
#include <SFML/Audio.hpp>
#include "../managers/sound_manager.hpp"
#include "../engine_api.hpp"

class ENGINE_API SoundComponent : public Component
{
    friend SoundManager;

public:

    void set_sound(const std::string &_sound_path);

private:
    SoundComponent() = default;
    SoundComponent(SoundComponent const&) = delete;
    void operator=(SoundComponent const&) = delete;

    sf::Music _music;
};