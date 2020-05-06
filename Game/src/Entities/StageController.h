#pragma once

namespace Engine 
{
    class EntityManager;
    struct Texture;
}

namespace Game
{
    class StageController
    {
    public:
        bool Init(Engine::EntityManager* entityManager_, int window_width, int window_height, Engine::Texture* texture);
    };
}
