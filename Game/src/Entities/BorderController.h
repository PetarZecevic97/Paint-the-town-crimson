#pragma once

namespace Game
{
    class BorderController
    {
    public:
        bool Init(Engine::EntityManager* entityManager_, int window_width, int window_height, Engine::Texture* texture);
    };
}
