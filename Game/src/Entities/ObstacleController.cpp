#include "precomp.h"

#include "ObstacleController.h"
#include "Misc.h"

namespace Game
{
	bool ObstacleController::Init(Engine::EntityManager* entityManager, Engine::Texture* texture, int numberOfObstacles)
	{
		ASSERT(entityManager != nullptr, "Must pass valid pointer to entitymanager to WaterNPCCOntroller::Init()");
		ASSERT(texture != nullptr, "Must pass valid pointer to texture to WaterNPCCOntroller::Init()");

		
		auto obstacle = std::make_unique<Engine::Entity>();

		switch (gLevelNumber)
		{
		case LevelNumber::LEVEL_ONE:
			break;
		case LevelNumber::LEVEL_TWO:


			//enemy->AddComponent<Engine::TransformComponent>(m_SpawnPositions[randomPosition].x, m_SpawnPositions[randomPosition].y, 50.f, 50.f);
			obstacle->AddComponent<Engine::TransformComponent>(spawnPosition.x, spawnPosition.y, 50.f, 50.f);


			obstacle->AddComponent<Engine::CollisionComponent>(50.f, 50.f);
			obstacle->AddComponent<Engine::ObstacleComponent>();
			obstacle->AddComponent<Engine::SpriteComponent>().m_Image = texture;
			entityManager->AddEntity(std::move(obstacle));
			break;
		case LevelNumber::LEVEL_THREE:
			//enemy->AddComponent<Engine::TransformComponent>(m_SpawnPositions[randomPosition].x, m_SpawnPositions[randomPosition].y, 50.f, 50.f);
			obstacle->AddComponent<Engine::TransformComponent>(spawnPosition.x, spawnPosition.y, 50.f, 50.f);


			obstacle->AddComponent<Engine::CollisionComponent>(50.f, 50.f);
			obstacle->AddComponent<Engine::ObstacleComponent>();
			obstacle->AddComponent<Engine::SpriteComponent>().m_Image = texture;
			entityManager->AddEntity(std::move(obstacle));
			break;
		default:
			break;
		}

	
		

		return true;
	}

	void ObstacleController::Update(float dt, Engine::EntityManager* entityManager)
	{
		auto ewaterNPC = entityManager->GetAllEntitiesWithComponent<Engine::ObstacleComponent>();

		for (auto& enemy : ewaterNPC)
		{
			// CPU
		}
	}

	bool ObstacleController::ShutDown()
	{
		return true;
	}
}