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
        // Method that advances the stage to the next level, or game over/win screen.
        void Update(Engine::EntityManager* entityManager_, int window_width, int window_height, bool isGameOver_, Engine::AudioSystem * audioSystem_, bool isTitleScreen);
        //Function that determines if the title screen should be animated or removed to make way for level 1
        bool UpdateIsTitleSceen(Engine::EntityManager* entityManager_);
    };
}
