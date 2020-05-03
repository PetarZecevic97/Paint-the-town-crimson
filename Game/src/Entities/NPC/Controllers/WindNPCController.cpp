#include "precomp.h"

#include "WindNPCController.h"

#include "Entities/NPC/EnemySpecificEntities.h"

namespace Game
{
	bool WindNPCController::Init(Engine::EntityManager* entityManager, Engine::Texture* texture, vec2 spawnPosition)
	{
		ASSERT(entityManager != nullptr, "Must pass valid pointer to entitymanager to WindNPCCOntroller::Init()");
		ASSERT(texture != nullptr, "Must pass valid pointer to texture to WindNPCCOntroller::Init()");

		auto enemy = std::make_unique<Engine::Entity>();
		enemy->AddComponent<Engine::NPCComponent>();
		enemy->AddComponent<EnemyComponent>(EnemyType::Wind);
		enemy->AddComponent<WindNPCComponent>();
		enemy->AddComponent<Engine::TransformComponent>(spawnPosition.x, spawnPosition.y, 50.f, 50.f);
		enemy->AddComponent<Engine::CollisionComponent>(50.f, 50.f);
		enemy->AddComponent<Engine::MoverComponent>();
		enemy->AddComponent<Engine::SpriteComponent>().m_Image = texture;
		entityManager->AddEntity(std::move(enemy));

		return true;
	}

	void WindNPCController::Update(float dt, Engine::EntityManager* entityManager)
	{
		auto ewindNPC = entityManager->GetAllEntitiesWithComponent<WindNPCComponent>();

		for (auto& enemy : ewindNPC)
		{
			auto mover = enemy->GetComponent<Engine::MoverComponent>();
			mover->m_TranslationSpeed.x = mover->m_TranslationSpeed.x * 1.75f;
			mover->m_TranslationSpeed.y = mover->m_TranslationSpeed.y * 1.75f;
		}
	}

	bool WindNPCController::ShutDown()
	{
		return true;
	}
}
