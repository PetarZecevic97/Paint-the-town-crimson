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
		auto npcs = entityManager->GetAllEntitiesWithComponents<NPCComponent,TransformComponent, MoverComponent>();

		for (auto& npc : npcs)
		{
			auto transform = npc->GetComponent<TransformComponent>();
			auto mover = npc->GetComponent<MoverComponent>();

			auto players = entityManager->GetAllEntitiesWithComponents<PlayerComponent>();
			
			ASSERT(players.size() <= 1, "Number of players are greater than one!");

			//int x = 1;
			//Move
			//vec2 playerPosition = players[0]->GetComponent<TransformComponent>()->m_Position;
			//float tg = std::tan(playerPosition.y/playerPosition.x);
			//transform->m_Position += mover->m_TranslationSpeed * dt*tg;
			//transform->m_Rotation += mover->m_RotationSpeed * dt*tg;

		}
	}
}
