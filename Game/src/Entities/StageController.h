#pragma once
#include "Misc.h"

namespace Engine 
{
    class EntityManager;
    struct Texture;
}

namespace Game
{
    class StageController
    {
    private:
        LevelNumber m_currentLevelNo;
    public:
        bool Init(Engine::EntityManager* entityManager_, int window_width, int window_height, Engine::Texture* texture);
        void Update(Engine::EntityManager* entityManager_, int window_width, int window_height, bool isGameOver_);
    };
}
