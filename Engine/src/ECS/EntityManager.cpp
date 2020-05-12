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
        m_Entities.push_back(std::move(e));
    }

	void EntityManager::RemoveEntity(long int id)
	{

        m_Entities.erase(std::find_if(m_Entities.begin(), m_Entities.end(), [id](auto& entity) {
            return entity->GetId() == id;
        }));

	}
    void EntityManager::RemoveAllEntities()
    {

        m_Entities.erase(std::begin(m_Entities), std::end(m_Entities));

    }
}
