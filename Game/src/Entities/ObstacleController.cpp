#include "precomp.h"

#include "ObstacleController.h"
#include "Misc.h"
#include <cmath>
#include <vector>
# define M_PI          3.141592653589793238462643383279502884L /* pi */


namespace Game
{
	bool ObstacleController::Init(Engine::EntityManager* entityManager, Engine::Texture* texture, LevelNumber levelNo, int width, int height)
	{
		ASSERT(entityManager != nullptr, "Must pass valid pointer to entitymanager to ObstacleCOntroller::Init()");
		ASSERT(texture != nullptr, "Must pass valid pointer to texture to ObstacleCOntroller::Init()");

		
		

		// Brancing depending on the level in question
		switch (levelNo)
		{
			case LevelNumber::LEVEL_ONE:
			{

				break;
			}
			case LevelNumber::LEVEL_THREE:
			{
				std::vector < std::pair<int, int> > lObstacleLocations;
				lObstacleLocations.push_back(std::make_pair(0.8 * height / 4,0));
				lObstacleLocations.push_back(std::make_pair(-0.8 * height / 4, 0));
				lObstacleLocations.push_back(std::make_pair(0, 0.8 * height / 4));
				lObstacleLocations.push_back(std::make_pair(0, -0.8 * height / 4));
				for (auto loc : lObstacleLocations)
				{
					
					auto obstacle = std::make_unique<Engine::Entity>();
					obstacle->AddComponent<Engine::SpriteComponent>().m_Image = texture;
					auto* sprite = obstacle->GetComponent<Engine::SpriteComponent>();
					SDL_Rect new_rect = { 0, 0, 50, 50 };
					sprite->m_src = new_rect;
					sprite->m_Animation = true;

					obstacle->AddComponent<Engine::TransformComponent>(static_cast<float>(loc.first), loc.second, 50.f, 50.f);
					obstacle->AddComponent<Engine::CollisionComponent>(50.f, 50.f);
					obstacle->AddComponent<Engine::ObstacleComponent>();
					obstacle->AddComponent<Engine::WallComponent>();   // Dodato da bi mogli majmuni (enemies) izbegavati obstacles

					entityManager->AddEntity(std::move(obstacle));
				}

				break;
			}
			case LevelNumber::LEVEL_TWO:
			{
				std::vector < std::pair<int, int> > lObstacleLocations;

				lObstacleLocations.push_back(std::make_pair(0.8 * height / 3, 0.8 * height / 3 - 60));
				lObstacleLocations.push_back(std::make_pair(0.8 * height / 3, 0.8 * height / 3 - 120));
				lObstacleLocations.push_back(std::make_pair(0.8 * height / 3, 0.8 * height / 3));
				lObstacleLocations.push_back(std::make_pair(0.8 * height / 3 - 60, 0.8 * height / 3));
				lObstacleLocations.push_back(std::make_pair(0.8 * height / 3 - 120, 0.8 * height / 3));

				lObstacleLocations.push_back(std::make_pair(0.8 * -height / 3, 0.8 * height / 3 - 60));
				lObstacleLocations.push_back(std::make_pair(0.8 * -height / 3, 0.8 * height / 3 - 120));
				lObstacleLocations.push_back(std::make_pair(0.8 * -height / 3, 0.8 * height / 3));
				lObstacleLocations.push_back(std::make_pair(0.8 * -height / 3 + 60, 0.8 * height / 3));
				lObstacleLocations.push_back(std::make_pair(0.8 * -height / 3 + 120, 0.8 * height / 3));

				lObstacleLocations.push_back(std::make_pair(0.8 * height / 3, 0.8 * -height / 3 + 60));
				lObstacleLocations.push_back(std::make_pair(0.8 * height / 3, 0.8 * -height / 3 + 120));
				lObstacleLocations.push_back(std::make_pair(0.8 * height / 3, 0.8 * -height / 3));
				lObstacleLocations.push_back(std::make_pair(0.8 * height / 3 - 60, 0.8 * -height / 3));
				lObstacleLocations.push_back(std::make_pair(0.8 * height / 3 - 120, 0.8 * -height / 3));

				lObstacleLocations.push_back(std::make_pair(0.8 * -height / 3, 0.8 * -height / 3 + 60));
				lObstacleLocations.push_back(std::make_pair(0.8 * -height / 3, 0.8 * -height / 3 + 120));
				lObstacleLocations.push_back(std::make_pair(0.8 * -height / 3, 0.8 * -height / 3));
				lObstacleLocations.push_back(std::make_pair(0.8 * -height / 3 + 60, 0.8 * -height / 3));
				lObstacleLocations.push_back(std::make_pair(0.8 * -height / 3 + 120, 0.8 * -height / 3));


				for (auto loc : lObstacleLocations)
				{

					auto obstacle = std::make_unique<Engine::Entity>();
					obstacle->AddComponent<Engine::SpriteComponent>().m_Image = texture;
					auto* sprite = obstacle->GetComponent<Engine::SpriteComponent>();
					SDL_Rect new_rect = { 0, 50, 50, 50 };
					sprite->m_src = new_rect;
					sprite->m_Animation = true;

					obstacle->AddComponent<Engine::TransformComponent>(loc.first+0.06*width, loc.second, 50.f, 50.f);
					obstacle->AddComponent<Engine::CollisionComponent>(50.f, 50.f);
					obstacle->AddComponent<Engine::ObstacleComponent>();
					obstacle->AddComponent<Engine::WallComponent>();   // Dodato da bi mogli majmuni (enemies) izbegavati obstacles

					entityManager->AddEntity(std::move(obstacle));
				}

				break;
			}


			default:
			{
				auto obstacle = std::make_unique<Engine::Entity>();
				obstacle->AddComponent<Engine::SpriteComponent>().m_Image = texture;
				auto* sprite = obstacle->GetComponent<Engine::SpriteComponent>();
				SDL_Rect new_rect = { 0, 100, 50, 50 };
				sprite->m_src = new_rect;
				sprite->m_Animation = true;

				obstacle->AddComponent<Engine::TransformComponent>(width / 4, height / 4, 50.f, 50.f);
				obstacle->AddComponent<Engine::CollisionComponent>(50.f, 50.f);
				obstacle->AddComponent<Engine::ObstacleComponent>();
				obstacle->AddComponent<Engine::WallComponent>();   // Dodato da bi mogli majmuni (enemies) izbegavati obstacles

				entityManager->AddEntity(std::move(obstacle));

				break;
			}
		}
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