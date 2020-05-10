#include "precomp.h"
#include "AudioSystem.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>

bool Game::AudioSystem::Init()
{
    //Initialize SDL audio
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        LOG_CRITICAL("Unable to initialize SDL audio. SDL error: {}", Mix_GetError());
        return false;
    }

    //Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        LOG_CRITICAL("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }
	return false;
}

bool Game::AudioSystem::Shutdown() 
{
    LOG_INFO("Shutting down AudioSystem");

    for (std::pair<std::string, Mix_Chunk*> element : m_SoundEffectLibrary)
    {
        Mix_FreeChunk(element.second);
        element.second = NULL;
        m_SoundEffectLibrary.erase(element.first);
    }

    for (std::pair<std::string, Mix_Music*> element : m_MusicLibrary)
    {
        Mix_FreeMusic(element.second);
        element.second = NULL;
        m_MusicLibrary.erase(element.first);
    }

    Mix_Quit();

    return true;
}


bool Game::AudioSystem::LoadMusic(std::string path_, std::string name_)
{
    Mix_Music* music = NULL;
    
    //Load music
    music = Mix_LoadMUS(path_.c_str());
    if (music == NULL)
    {
        LOG_CRITICAL("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }
    
    m_MusicLibrary.insert(std::pair(name_, std::move(music)));

    return true;
}

bool Game::AudioSystem::LoadSoundEffect(std::string path_, std::string name_)
{
    Mix_Chunk* effect = NULL;

    //Load music
    effect = Mix_LoadWAV(path_.c_str());
    if (effect == NULL)
    {
        LOG_CRITICAL("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }
    m_SoundEffectLibrary.insert(std::pair(name_, std::move(effect)));
    Mix_Volume(-1, 15);
    return true;
}

bool Game::AudioSystem::PlayBackgroundMusic(std::string musicName_) 
{
    //If there is no music playing
    if (Mix_PlayingMusic() == 0)
    {
        //Play the music
        Mix_PlayMusic(m_MusicLibrary[musicName_], -1);
    }
    else
    {
        Mix_HaltMusic();
        Mix_PlayMusic(m_MusicLibrary[musicName_], -1);
    }
    Mix_VolumeMusic(20);
    return true;
}

bool Game::AudioSystem::PlaySoundEffect(std::string SfxName_)
{
    Mix_PlayChannel(-1, m_SoundEffectLibrary[SfxName_], 0);
    return true;
}

bool Game::AudioSystem::PlaySoundEffectOnLoop(std::string SfxName_, int nLoops) {
    Mix_PlayChannel(-1, m_SoundEffectLibrary[SfxName_], nLoops);
    return true;
}

bool Game::AudioSystem::StopMusic()
{
    Mix_HaltMusic();
    return false;
}


