#pragma once

namespace Engine
{
    class EntityManager;

    class PhysicsSystem
    {
    public:
        bool Init();
        void Update(float dt, EntityManager* entityManager);

    private:
    };
}