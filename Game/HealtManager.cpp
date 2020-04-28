#include "precomp.h"

#include "HealtManager.h"

namespace Game
{

	HealtManager* HealtManager::Get()
	{
		ASSERT(m_Instance != nullptr, "Healt Manager is not initialized!");
		return m_Instance;
	}

	bool HealtManager::Init()
	{
		m_Instance = new HealtManager();
		return true;
	}

	bool HealtManager::ShutDown()
	{
		return true;
	}

	void HealtManager::UpdateEntityHealt(Engine::Entity* collider)
	{
		auto colliderHealt = collider->GetComponent<Engine::HealthComponent>();
		
		ASSERT(colliderHealt != nullptr, "Collider has no healt!");

		auto collidedWith = collider->GetComponent<Engine::CollisionComponent>()->m_CollidedWith;
		for (auto& entity : collidedWith)
		{
			auto healt = entity->GetComponent<Engine::HealthComponent>();
			if (healt != nullptr)
			{
				colliderHealt -= 10;
			}
		}
	}
}