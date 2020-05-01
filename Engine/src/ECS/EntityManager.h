#pragma once
#include "ECS/Entity.h"

#define MAX_NEW_ELEMENTS (50)
#define ON_START_ELEMENTS (50)

namespace Engine
{
    struct Texture;

    class EntityManager
    {
    public:
        bool Init();
        void Update(float dt);
        void AddEntity(Entity* e);
        void AddEntity(std::unique_ptr<Entity>&& e);

        template <typename TComponent>
        auto GetAllEntitiesWithComponent()
        {
            std::vector<Entity*> returnVec{};

            for (const auto& entity : m_Entities)
            {
                if (entity != nullptr && entity->HasComponent<TComponent>())
                {
                    returnVec.push_back(entity.get());
                }
            }

            return returnVec;
        }


        template <typename TComponent>
        auto GetAllEntitiesWithComponentFromVector(std::vector<Entity*>& vector_)
        {
            std::vector<Entity*> returnVec{};

            for (const auto& entity : vector_)
            {
                if (entity != nullptr && entity->HasComponent<TComponent>())
                {
                    returnVec.push_back(entity);
                }
            }

            return returnVec;
        }

        template <typename... TComponent>
        auto GetAllEntitiesWithComponents()
        {
            std::vector<Entity*> returnVec{};

            for (const auto& entity : m_Entities)
            {
                if (entity != nullptr && entity->HasComponents<TComponent...>())
                {
                    returnVec.push_back(entity.get());
                }
            }

            return returnVec;
        }

        template <typename TComponent>
        auto GetAllComponentInstances()
        {
            std::vector<TComponent*> returnVec{};

            for (const auto& entity : m_Entities)
            {
                if (entity != nullptr)
                {
                    TComponent* component = entity->GetComponent<TComponent>();
                        if (component)
                        {
                            returnVec.push_back(component);
                        }
                }
            }

            return returnVec;
        }

        EntityManager() = default;
    private:
        using EntityList = std::vector<std::unique_ptr<Entity>>;

        EntityList m_Entities{ ON_START_ELEMENTS };

        unsigned m_CurrentElement = 0;
        unsigned m_MinimalFreeElement = 0;

        EntityManager(const EntityManager& other) = delete;
        EntityManager& operator=(EntityManager& other) = delete;
    };

}
