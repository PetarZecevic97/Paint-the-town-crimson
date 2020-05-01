#include "precomp.h"
#include "EntityManager.h"
#include "ECS/Entity.h"
#include "Render/Texture.h"

namespace Engine
{
    bool EntityManager::Init()
    {
        return true;
    }

    void EntityManager::Update(float dt)
    {
        // Post-physics update
    }

    void EntityManager::AddEntity(Entity* e)
    {
        m_Entities.emplace_back(e);
    }
    void EntityManager::AddEntity(std::unique_ptr<Entity>&& e)
    {
        if(m_Entities.size() <= m_CurrentElement)
        {
            m_Entities.resize(MAX_NEW_ELEMENTS);
        }
        ASSERT(m_Entities.size() > m_CurrentElement, "Entity array is full! Resizze failed!");
        m_Entities[m_CurrentElement] = std::move(e);
        m_CurrentElement++;
    }
}
