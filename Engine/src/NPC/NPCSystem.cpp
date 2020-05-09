#include "precomp.h"

#include "NPCSystem.h"

#include "ECS/EntityManager.h"
#include "ECS/Component.h"

#define STEP  2 // STEP * SPEED =>  0.1*100
#define MAX_PATHFINDING_ITERATIONS 12 //Num of iterations for ray casting

namespace Engine
{
	bool NPCSystem::Init()
	{
		return true;
	}

	void NPCSystem::Update(float dt, EntityManager* entityManager)
	{
		constexpr float pi = 3.1415926535897932;
		constexpr float twoPI = pi * 2.f;

		//??? Optimization with GetAllEntitiesWithComponentFromVector() ???

		auto npcs = entityManager->GetAllEntitiesWithComponents<NPCComponent, TransformComponent, MoverComponent>();
		auto send = entityManager->GetAllEntitiesWithComponent<WallComponent>();
		auto players = entityManager->GetAllEntitiesWithComponents<PlayerComponent>();

		ASSERT(players.size() <= 1, "Number of players are greater than one!");

		auto pmover = players[0]->GetComponent<TransformComponent>();

		for (auto& npc : npcs)
		{
			auto transform = npc->GetComponent<TransformComponent>();
			auto mover = npc->GetComponent<MoverComponent>();

			float angle = std::atan((pmover->m_Position.y - transform->m_Position.y)
				/
				(pmover->m_Position.x - transform->m_Position.x));

			if (pmover->m_Position.x < transform->m_Position.x)
			{
				angle = angle + pi;
			}

			DodgeWalls(npc);

			float addition = 0;
			int npcLookFactor = npc->GetComponent<NPCComponent>()->m_SideToLook;
			while (CheckRayCasting(npc, angle, send))
			{
				if (addition >= twoPI)
				{
					break;
				}
				addition += pi / 4;
				if (addition >= (pi))
				{
					npc->GetComponent<NPCComponent>()->m_SideToLook = -npcLookFactor;
					angle = angle + npcLookFactor* addition;
				}
				angle = angle + npcLookFactor* pi / 4;

			}

			//Petar je menjao ovde kod!
			if (players[0]->GetComponent<Engine::PlayerComponent>()->m_timeoutBuff)
			{
				mover->m_TranslationSpeed.x = 0.f;
				mover->m_TranslationSpeed.y = 0.f;
			}
			else
			{

				mover->m_TranslationSpeed.x = (addition < twoPI) ? (std::cosf(angle) * 200.f) : (-mover->m_TranslationSpeed.x);
				mover->m_TranslationSpeed.y = (addition < twoPI) ? (std::sinf(angle) * 200.f) : (-mover->m_TranslationSpeed.y);
			}

		}
	}

	void NPCSystem::DodgeWalls(Entity* npc)
	{
		auto coll = npc->GetComponent<CollisionComponent>()->m_CollidedWith;
		for (auto& coller : coll)
		{
			if (coller->GetId() > 10000000) {
				continue;
			}
			if (coller->HasComponent<WallComponent>())
			{
				npc->GetComponent<MoverComponent>()->m_TranslationSpeed.x = -npc->GetComponent<MoverComponent>()->m_TranslationSpeed.x;
				npc->GetComponent<MoverComponent>()->m_TranslationSpeed.y = -npc->GetComponent<MoverComponent>()->m_TranslationSpeed.y;
			}
		}
	}

	bool NPCSystem::CheckRayCasting(Entity* npc, double angle, std::vector<Entity*>& possibleCooliders)
	{
		const float deltaX = static_cast<float>(std::cos(angle) * STEP);
		const float deltaY = static_cast<float>(std::sin(angle) * STEP);
		for (auto& collider : possibleCooliders)
		{
			if (collider == npc)
			{
				LOG_WARNING("Checking RAY Casting for same object!");
				continue;
			}

			auto npcTransform = npc->GetComponent<TransformComponent>()->m_Position;
			auto npcCollision = npc->GetComponent<CollisionComponent>();

			auto colliderTransform = collider->GetComponent<TransformComponent>();
			auto colliderCollision = collider->GetComponent<CollisionComponent>();

			for(unsigned i = 0;i<MAX_PATHFINDING_ITERATIONS;i++)
			{
				bool collisionX = npcTransform.x + npcCollision->m_Size.x / 2.f >= colliderTransform->m_Position.x - colliderCollision->m_Size.x / 2.f &&
					colliderTransform->m_Position.x + colliderCollision->m_Size.x / 2.f >= npcTransform.x - npcCollision->m_Size.x / 2.f;

				bool collisionY = npcTransform.y + npcCollision->m_Size.y / 2.f >= colliderTransform->m_Position.y - colliderCollision->m_Size.y / 2.f &&
					colliderTransform->m_Position.y + colliderCollision->m_Size.y / 2.f >= npcTransform.y - npcCollision->m_Size.y / 2.f;

				if (collisionX && collisionY)
				{
					return true;
				}
				npcTransform.x += deltaX;
				npcTransform.y += deltaY;
			}
		}
		return false;
	}
}
