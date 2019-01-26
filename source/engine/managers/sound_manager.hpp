#pragma once

#include "../engine_api.hpp"
#include <unordered_map>

class SoundComponent;
class Component;
class Entity;

class ENGINE_API SoundManager
{
public:

    static SoundManager* get();

    SoundComponent *load_sound_component(Entity *_entity, const std::string &_sound_file, const std::string &_sound_type);
    void play_sound(const std::string &_sound_type, bool repeat = false);
    void stop_sound(const std::string& sound_type);
    void start_up();
    void shut_down();

    void deregister_sound_component(SoundComponent* sound);

private:
    SoundManager() = default;
    ~SoundManager() = default;

    SoundManager(SoundManager const&) = delete;
    void operator=(SoundManager const&) = delete;
    std::unordered_map<std::string, SoundComponent *> _sound_components;
    std::vector<SoundComponent *> _sound_components_vec;
};

