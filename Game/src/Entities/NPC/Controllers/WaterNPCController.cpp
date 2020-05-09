#include "precomp.h"

#include "WaterNPCController.h"

#include "Entities/NPC/EnemySpecificEntities.h"
#include "..//EnemyAnimation.h"

namespace Game
{
	bool WaterNPCController::Init(Engine::EntityManager* entityManager, Engine::Texture* texture, vec2 spawnPosition)
	{
		ASSERT(entityManager != nullptr, "Must pass valid pointer to entitymanager to WaterNPCCOntroller::Init()");
		ASSERT(texture != nullptr, "Must pass valid pointer to texture to WaterNPCCOntroller::Init()");

		auto enemy = std::make_unique<Engine::Entity>();
		enemy->AddComponent<Engine::NPCComponent>();
		enemy->AddComponent<EnemyComponent>(EnemyType::Water);
		enemy->AddComponent<WaterNPCComponent>();

		//enemy->AddComponent<Engine::TransformComponent>(m_SpawnPositions[randomPosition].x, m_SpawnPositions[randomPosition].y, 50.f, 50.f);
		enemy->AddComponent<Engine::TransformComponent>(spawnPosition.x, spawnPosition.y, 50.f, 50.f);
		enemy->AddComponent<Engine::CollisionComponent>(50.f, 50.f);
		enemy->AddComponent<Engine::MoverComponent>();
		enemy->AddComponent<Engine::HealthComponent>(2, 2);
		enemy->AddComponent<Engine::SpriteComponent>().m_Image = texture;
		auto* sprite = enemy->GetComponent<Engine::SpriteComponent>();
		SDL_Rect new_rect{ 0, 0, 50, 50 };
		sprite->m_src = new_rect;
		sprite->m_Animation = true;
		entityManager->AddEntity(std::move(enemy));

		return true;
	}

	void WaterNPCController::Update(float dt, Engine::EntityManager* entityManager)
	{
		auto ewaterNPC = entityManager->GetAllEntitiesWithComponent<WaterNPCComponent>();

		for (auto& enemy : ewaterNPC)
		{
			// CPU
			ElementalAnimation(entityManager->GetAllEntitiesWithComponent<Engine::PlayerComponent>()[0], enemy, 0);
		}
	}

	bool WaterNPCController::ShutDown()
	{
		return true;
	}
}