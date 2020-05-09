#pragma once
#include <SDL.h>
#include <SDL_mixer.h>

namespace Engine
{
    struct WindowData;
    class Renderer;
    class Entity;
    class EntityManager;

    class AudioSystem
    {
    public:
        bool Init();
        bool Shutdown();
        bool LoadMusic(std::string path_, std::string name);
        bool LoadSoundEffect(std::string path_, std::string name_);
        bool PlayBackgroundMusic(std::string musicName_);
        bool PlaySoundEffect(std::string sfxName_);

        AudioSystem() = default;
    private:
 
        AudioSystem(const AudioSystem& other) = delete;
        AudioSystem& operator=(AudioSystem& other) = delete;
        std::unordered_map<std::string, Mix_Chunk*> m_SoundEffectLibrary;
        std::unordered_map<std::string, Mix_Music*> m_MusicLibrary;
    };
}
