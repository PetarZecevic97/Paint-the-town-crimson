#pragma once

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
        void Update(float dt, Engine::EntityManager* entityManager_);
        //int m_fireball_cooldown{ 100 };
        int m_last_fired_time{ -100 };
        //int m_number_of_lives{ 3 };
    };

    bool CreateItem(Engine::EntityManager* entityManager_, int item_type, Engine::Texture* texture, Engine::Entity* npc);
    void UpdateItems(Engine::EntityManager* entityManager_);

    bool CreateFireball(Engine::EntityManager* entityManager_, int direction, int direction2);
    void UpdateFireballs(Engine::EntityManager* entityManager_);

}