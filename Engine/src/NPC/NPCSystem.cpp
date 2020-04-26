#include "precomp.h"

#include "NPCSystem.h"

#include "ECS/EntityManager.h"
#include "ECS/Component.h"

namespace Engine
{
	bool NPCSystem::Init()
	{
		return true;
	}

	void NPCSystem::Update(float dt, EntityManager* entityManager)
	{
		const double pi = 3.1415926535897932;
		auto npcs = entityManager->GetAllEntitiesWithComponents<NPCComponent,TransformComponent, MoverComponent>();

		for (auto& npc : npcs)
		{
			auto transform = npc->GetComponent<TransformComponent>();
			auto mover = npc->GetComponent<MoverComponent>();

			auto players = entityManager->GetAllEntitiesWithComponents<PlayerComponent>();		
			ASSERT(players.size() <= 1, "Number of players are greater than one!");

			if (players.size() == 1)
			{
				auto pmover = players[0]->GetComponent<TransformComponent>();

				double angle = std::atan((pmover->m_Position.y - transform->m_Position.y)
														       /
										 (pmover->m_Position.x - transform->m_Position.x));

				if (pmover->m_Position.x < transform->m_Position.x)
				{
					angle = angle + pi;
				}
				mover->m_TranslationSpeed = { std::cos(angle) * 100, std::sin(angle) * 100 };
			}
		}
	}
}
