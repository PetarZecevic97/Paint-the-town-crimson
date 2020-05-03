#include "precomp.h"

#include "FireNPCController.h"

#include "Entities/NPC/EnemySpecificEntities.h"

namespace Game
{
	bool FireNPCController::Init(Engine::EntityManager* entityManager, Engine::Texture* texture, vec2 spawnPosition)
	{
		ASSERT(entityManager != nullptr, "Must pass valid pointer to entitymanager to WaterNPCCOntroller::Init()");
		ASSERT(texture != nullptr, "Must pass valid pointer to texture to WaterNPCCOntroller::Init()");

		auto enemy = std::make_unique<Engine::Entity>();
		enemy->AddComponent<Engine::NPCComponent>();
		enemy->AddComponent<EnemyComponent>(EnemyType::Fire);
		enemy->AddComponent<WaterNPCComponenet>();
		enemy->AddComponent<Engine::TransformComponent>(spawnPosition.x, spawnPosition.y, 50.f, 50.f);
		enemy->AddComponent<Engine::CollisionComponent>(50.f, 50.f);
		enemy->AddComponent<Engine::MoverComponent>();
		enemy->AddComponent<Engine::SpriteComponent>().m_Image = texture;
		entityManager->AddEntity(std::move(enemy));

		return true;
	}

	void FireNPCController::Update(float dt, Engine::EntityManager* entityManager)
	{
		auto ewaterNPC = entityManager->GetAllEntitiesWithComponent<FireNPCComponent>();

		for (auto& enemy : ewaterNPC)
		{
			// CPU
		}
	}

	bool FireNPCController::ShutDown()
	{
		return true;
	}
}
