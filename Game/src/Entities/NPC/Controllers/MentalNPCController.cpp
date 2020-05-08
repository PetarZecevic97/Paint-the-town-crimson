#include "precomp.h"

#include "MentalNPCController.h"

#include "Entities/NPC/EnemySpecificEntities.h"
#include "..//EnemyAnimation.h"

namespace Game
{
	bool MentalNPCController::Init(Engine::EntityManager* entityManager, Engine::Texture* texture, vec2 spawnPosition)
	{
		ASSERT(entityManager != nullptr, "Must pass valid pointer to entitymanager to MentalNPCController::Init()");
		ASSERT(texture != nullptr, "Must pass valid pointer to texture to MentalNPCController::Init()");

		auto enemy = std::make_unique<Engine::Entity>();
		enemy->AddComponent<Engine::NPCComponent>();
		enemy->AddComponent<EnemyComponent>(EnemyType::Mental);
		enemy->AddComponent<MentalNPCComponent>();

		//enemy->AddComponent<Engine::TransformComponent>(m_SpawnPositions[randomPosition].x, m_SpawnPositions[randomPosition].y, 50.f, 50.f);
		enemy->AddComponent<Engine::TransformComponent>(spawnPosition.x, spawnPosition.y, 50.f, 50.f);
		enemy->AddComponent<Engine::CollisionComponent>(50.f, 50.f);
		enemy->AddComponent<Engine::MoverComponent>();
		enemy->AddComponent<Engine::HealthComponent>(1, 1);
		enemy->AddComponent<Engine::SpriteComponent>().m_Image = texture;
		auto* sprite = enemy->GetComponent<Engine::SpriteComponent>();
		SDL_Rect new_rect{ 0, 0, 50, 50 };
		sprite->m_src = new_rect;
		sprite->m_Animation = true;
		entityManager->AddEntity(std::move(enemy));

		return true;
	}

	void MentalNPCController::Update(float dt, Engine::EntityManager* entityManager)
	{
		auto ementalNPC = entityManager->GetAllEntitiesWithComponent<MentalNPCComponent>();

		for (auto& enemy : ementalNPC)
		{
			// CPU
			ElementalAnimation(entityManager->GetAllEntitiesWithComponent<Engine::PlayerComponent>()[0], enemy, 2);
		}
	}

	bool MentalNPCController::ShutDown()
	{
		return true;
	}
}