#include "precomp.h"

#include "EnemyController.h"

#include "Entities/NPC/EnemySpecificEntities.h"

#include <random>

namespace Game
{
	bool EnemyController::Init(Engine::EntityManager* entityManager, Engine::Texture* texture)
	{
		ASSERT(entityManager != nullptr, "Must pass valid pointer to entitymanager to EnemyController::Init()");
		ASSERT(texture != nullptr, "Must pass valid pointer to texture to EnemyController::Init()");
		
		auto enemy = std::make_unique<Engine::Entity>();

		enemy->AddComponent<EnemyComponent>();
		enemy->AddComponent<Engine::NPCComponent>();
		enemy->AddComponent<Engine::TransformComponent>(0.f, 0.f, 50.f, 50.f);
		enemy->AddComponent<Engine::CollisionComponent>(30.f, 30.f);
		enemy->AddComponent<Engine::MoverComponent>(100.f, 100.f);
		enemy->AddComponent<Engine::SpriteComponent>().m_Image = texture;

		entityManager->AddEntity(std::move(enemy));
		return true;
	}

	void EnemyController::Update(float dt, Engine::EntityManager* entityManager)
	{
		auto enemies = entityManager->GetAllEntitiesWithComponent<EnemyComponent>();

		for (auto& enemy : enemies)
		{
			auto mover = enemy->GetComponent<Engine::MoverComponent>();
			mover->m_TranslationSpeed = { mover->m_TranslationSpeed.x, mover->m_TranslationSpeed.y };
		}
	}
}

