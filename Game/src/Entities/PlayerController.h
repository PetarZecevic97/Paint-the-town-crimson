#pragma once
#include <precomp.cpp>


namespace Engine
{
    class EntityManager;
    class TextureManager;
}

namespace Game
{
    
    class PlayerController
    {
    public:
        bool Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_);
        void Update(float dt, Engine::EntityManager* entityManager_, Engine::AudioSystem* audioSystem_);
        int m_last_fired_time{ -100 };
        
    };

    //bool CreateItem(Engine::EntityManager* entityManager_, int item_type, Engine::Texture* texture, Engine::Entity* npc);
    //void UpdateItems(Engine::EntityManager* entityManager_);

    bool CreateFireball(Engine::EntityManager* entityManager_, int direction, int direction2);
    void UpdateFireballs(Engine::EntityManager* entityManager_, Engine::AudioSystem * audioSystem_);

}