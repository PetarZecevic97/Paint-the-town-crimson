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

		return true;
	}

	void EnemyController::Update(float dt, Engine::EntityManager* entityManager)
	{
		auto enemies = entityManager->GetAllEntitiesWithComponent<EnemyComponent>();

		for (auto& enemy : enemies)
		{
			// CPU
		}
	}
}

