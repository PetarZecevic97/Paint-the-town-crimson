#include "precomp.h"

#include "ObstacleController.h"
#include "Misc.h"

namespace Game
{
	bool ObstacleController::Init(Engine::EntityManager* entityManager, Engine::Texture* texture, LevelNumber levelNo, int width, int height)
	{
		ASSERT(entityManager != nullptr, "Must pass valid pointer to entitymanager to ObstacleCOntroller::Init()");
		ASSERT(texture != nullptr, "Must pass valid pointer to texture to ObstacleCOntroller::Init()");

		
		auto obstacle = std::make_unique<Engine::Entity>();
		SDL_Rect new_rect = { 0, 0, 50, 50 };
		switch (gLevelNumber)
		{
		case LevelNumber::LEVEL_ONE:
			obstacle->AddComponent<Engine::TransformComponent>(width / 2, height / 2, 50.f, 50.f);
			obstacle->AddComponent<Engine::CollisionComponent>(50.f, 50.f);
			obstacle->AddComponent<Engine::ObstacleComponent>();
			obstacle->AddComponent<Engine::ItemComponent>(SDL_GetTicks());
			obstacle->AddComponent<Engine::SpriteComponent>().m_Image = texture;
			break;

		case LevelNumber::LEVEL_TWO:
			obstacle->AddComponent<Engine::TransformComponent>(width / 2, height / 2, 50.f, 50.f);
			obstacle->AddComponent<Engine::CollisionComponent>(50.f, 50.f);
			obstacle->AddComponent<Engine::ObstacleComponent>();
			obstacle->AddComponent<Engine::ItemComponent>(SDL_GetTicks());
			obstacle->AddComponent<Engine::SpriteComponent>().m_Image = texture;


			break;

		case LevelNumber::LEVEL_THREE:
			obstacle->AddComponent<Engine::TransformComponent>(width / 2, height / 2, 50.f, 50.f);
			obstacle->AddComponent<Engine::CollisionComponent>(50.f, 50.f);
			obstacle->AddComponent<Engine::ObstacleComponent>();
			obstacle->AddComponent<Engine::ItemComponent>(SDL_GetTicks());
			obstacle->AddComponent<Engine::SpriteComponent>().m_Image = texture;


			break;

		default:
			obstacle->AddComponent<Engine::TransformComponent>(width / 2, height / 2, 50.f, 50.f);
			obstacle->AddComponent<Engine::CollisionComponent>(50.f, 50.f);
			obstacle->AddComponent<Engine::ObstacleComponent>();
			obstacle->AddComponent<Engine::ItemComponent>(SDL_GetTicks());
			obstacle->AddComponent<Engine::SpriteComponent>().m_Image = texture;
			break;
		}



		auto* sprite = obstacle->GetComponent<Engine::SpriteComponent>();
		
		sprite->m_src = new_rect;
		sprite->m_Animation = true;

		entityManager->AddEntity(std::move(obstacle));



		return true;
	}

	void ObstacleController::Update(float dt, Engine::EntityManager* entityManager)
	{
		auto obstacles = entityManager->GetAllEntitiesWithComponent<Engine::ObstacleComponent>();

		for (auto& obstacle : obstacles)
		{
			// CPU
		}
	}

	bool ObstacleController::ShutDown()
	{
		return true;
	}
}