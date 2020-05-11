#pragma once
#include <precomp.cpp>
#include "Audio System/AudioSystem.h"
#include "Entities/Misc.h"

namespace Engine
{
    class EntityManager;
    struct Texture;
}

namespace Game
{
    class PauseController
    {
    private:
        Engine::Texture* m_texture;
    public:
        bool Init(Engine::EntityManager* entityManager_, int window_width, int window_height, Engine::Texture* texture);
        bool Update(Engine::EntityManager* entityManager_, int window_width, int window_height, Engine::Texture* texture_, AudioSystem* audioSystem_, bool isTitleScreen_);
    };
}
