#pragma once
#include <precomp.cpp>
#include "Audio System/AudioSystem.h"
#include "Misc.h"

namespace Engine 
{
    class EntityManager;
    struct Texture;
    class AudioSystem;
}

namespace Game
{
    class StageController
    {
    public:
        LevelNumber m_currentLevelNo;
        bool Init(Engine::EntityManager* entityManager_, int window_width, int window_height, Engine::Texture* texture);
        void Update(Engine::EntityManager* entityManager_, int window_width, int window_height, bool isGameOver_, Engine::AudioSystem * audioSystem_, bool isTitleScreen);
    };
}
