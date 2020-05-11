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
		
		m_currentLevelNo == LevelNumber::LEVEL_MENU;

		m_height = height;
		m_width = width;
		
		// Wall init
		std::vector < std::pair<float, float> > lObstacleLocations;
		for (int i = 80; i < 1280; i += 55) 
		{
			if (i > 500 && i < 750)continue;
			lObstacleLocations.push_back(std::make_pair(-0.5f*width + i, height*0.5f-25.f));
			lObstacleLocations.push_back(std::make_pair(-0.5f * width + i, -height * 0.5f+25.f));
		}
		for (int i = 0; i < 720; i += 55)
		{
			if (i > 250 && i < 500)continue;
			lObstacleLocations.push_back(std::make_pair(0.5f * width-100.f, -height * 0.5f + i-25.f));
			lObstacleLocations.push_back(std::make_pair(-0.5f * width+80.f, -height * 0.5f + i-25.f));
		}

		for (auto loc : lObstacleLocations)
		{

			auto obstacle = std::make_unique<Engine::Entity>();
			obstacle->AddComponent<Engine::SpriteComponent>().m_Image = texture;
			auto* sprite = obstacle->GetComponent<Engine::SpriteComponent>();
			SDL_Rect new_rect = { 0, 0, 50, 50 };
			sprite->m_src = new_rect;
			sprite->m_Animation = true;

			obstacle->AddComponent<Engine::TransformComponent>(loc.first + 0.06f * m_width, loc.second, 50.f, 50.f);
			obstacle->AddComponent<Engine::CollisionComponent>(50.f, 50.f);
			obstacle->AddComponent<Engine::ObstacleComponent>();
			obstacle->AddComponent<Engine::WallComponent>();   // Dodato da bi mogli majmuni (enemies) izbegavati obstacles

			entityManager->AddEntity(std::move(obstacle));
		}
		
		
		
		return true;
	}

	void ObstacleController::Update(float dt, Engine::EntityManager* entityManager, Engine::TextureManager* textureManager, bool isGameOver)
	{
		auto obstacles = entityManager->GetAllEntitiesWithComponent<Engine::ObstacleComponent>();
		if (m_currentLevelNo == LevelNumber::LEVEL_MENU)m_currentLevelNo = LevelNumber::LEVEL_ONE;

		// Delete all Obstacle components
		for (auto obstacle : obstacles)
		{
			if (obstacle->HasComponent<Engine::InnerObstacleComponent>() || m_currentLevelNo == LevelNumber::LEVEL_THREE || isGameOver)
			{
				auto id = obstacle->GetId();
				entityManager->RemoveEntity(id);

			}
			else
			{
				if (m_currentLevelNo == LevelNumber::LEVEL_ONE) 
				{
					auto* sprite = obstacle->GetComponent<Engine::SpriteComponent>();
					SDL_Rect new_rect = { 0, 50, 50, 50 };
					sprite->m_src = new_rect;
				}
				else if (m_currentLevelNo == LevelNumber::LEVEL_TWO)
				{
					auto* sprite = obstacle->GetComponent<Engine::SpriteComponent>();
					SDL_Rect new_rect = { 0, 100, 50, 50 };
					sprite->m_src = new_rect;
				}
			}
		}
		if (!isGameOver)
		{
			if (m_currentLevelNo == LevelNumber::LEVEL_ONE)
			{

				auto obstacle = std::make_unique<Engine::Entity>();
				std::vector < std::pair<float, float> > lObstacleLocations;

				lObstacleLocations.push_back(std::make_pair(0.8f * m_height / 3.f, 0.8f * m_height / 3.f - 60.f));
				lObstacleLocations.push_back(std::make_pair(0.8f * m_height / 3, 0.8f * m_height / 3 - 120));
				lObstacleLocations.push_back(std::make_pair(0.8f * m_height / 3, 0.8f * m_height / 3));
				lObstacleLocations.push_back(std::make_pair(0.8f * m_height / 3 - 60, 0.8f * m_height / 3));
				lObstacleLocations.push_back(std::make_pair(0.8f * m_height / 3 - 120, 0.8f * m_height / 3));

				lObstacleLocations.push_back(std::make_pair(0.8f * -m_height / 3, 0.8f * m_height / 3 - 60));
				lObstacleLocations.push_back(std::make_pair(0.8f * -m_height / 3, 0.8f * m_height / 3 - 120));
				lObstacleLocations.push_back(std::make_pair(0.8f * -m_height / 3, 0.8f * m_height / 3));
				lObstacleLocations.push_back(std::make_pair(0.8f * -m_height / 3 + 60, 0.8f * m_height / 3));
				lObstacleLocations.push_back(std::make_pair(0.8f * -m_height / 3 + 120, 0.8f * m_height / 3));

				lObstacleLocations.push_back(std::make_pair(0.8f * m_height / 3, 0.8f * -m_height / 3 + 60));
				lObstacleLocations.push_back(std::make_pair(0.8f * m_height / 3, 0.8f * -m_height / 3 + 120));
				lObstacleLocations.push_back(std::make_pair(0.8f * m_height / 3, 0.8f * -m_height / 3));
				lObstacleLocations.push_back(std::make_pair(0.8f * m_height / 3 - 60, 0.8f * -m_height / 3));
				lObstacleLocations.push_back(std::make_pair(0.8f * m_height / 3 - 120, 0.8f * -m_height / 3));

				lObstacleLocations.push_back(std::make_pair(0.8f * -m_height / 3, 0.8f * -m_height / 3 + 60));
				lObstacleLocations.push_back(std::make_pair(0.8f * -m_height / 3, 0.8f * -m_height / 3 + 120));
				lObstacleLocations.push_back(std::make_pair(0.8f * -m_height / 3, 0.8f * -m_height / 3));
				lObstacleLocations.push_back(std::make_pair(0.8f * -m_height / 3 + 60, 0.8f * -m_height / 3));
				lObstacleLocations.push_back(std::make_pair(0.8f * -m_height / 3 + 120, 0.8f * -m_height / 3));


				for (auto loc : lObstacleLocations)
				{

					auto obstacle = std::make_unique<Engine::Entity>();
					obstacle->AddComponent<Engine::SpriteComponent>().m_Image = textureManager->GetTexture("obstacle");
					auto* sprite = obstacle->GetComponent<Engine::SpriteComponent>();
					SDL_Rect new_rect = { 0, 50, 50, 50 };
					sprite->m_src = new_rect;
					sprite->m_Animation = true;

					obstacle->AddComponent<Engine::TransformComponent>(loc.first + 0.06f * m_width, loc.second, 50.f, 50.f);
					obstacle->AddComponent<Engine::CollisionComponent>(50.f, 50.f);
					obstacle->AddComponent<Engine::ObstacleComponent>();

					obstacle->AddComponent<Engine::InnerObstacleComponent>();

					obstacle->AddComponent<Engine::WallComponent>();   // Dodato da bi mogli majmuni (enemies) izbegavati obstacles

					entityManager->AddEntity(std::move(obstacle));
				}
				m_currentLevelNo = LevelNumber::LEVEL_TWO;
				entityManager->AddEntity(std::move(obstacle));
			}
			else if (m_currentLevelNo == LevelNumber::LEVEL_TWO)
			{
				auto obstacle = std::make_unique<Engine::Entity>();

				std::vector < std::pair<float, float> > lObstacleLocations;
				lObstacleLocations.push_back(std::make_pair(0.8f * m_height / 4 + 50.f, 0.f));
				lObstacleLocations.push_back(std::make_pair(-0.8f * m_height / 4 + 50.f, 0.f));
				lObstacleLocations.push_back(std::make_pair(50.f, 0.8f * m_height / 4));
				lObstacleLocations.push_back(std::make_pair(50.f, -0.8f * m_height / 4));
				for (auto loc : lObstacleLocations)
				{

					auto obstacle = std::make_unique<Engine::Entity>();
					obstacle->AddComponent<Engine::SpriteComponent>().m_Image = textureManager->GetTexture("obstacle");
					auto* sprite = obstacle->GetComponent<Engine::SpriteComponent>();
					SDL_Rect new_rect = { 0, 100, 50, 50 };
					sprite->m_src = new_rect;
					sprite->m_Animation = true;

					obstacle->AddComponent<Engine::TransformComponent>(static_cast<float>(loc.first), loc.second, 50.f, 50.f);
					obstacle->AddComponent<Engine::CollisionComponent>(50.f, 50.f);
					obstacle->AddComponent<Engine::ObstacleComponent>();
					obstacle->AddComponent<Engine::InnerObstacleComponent>();
					obstacle->AddComponent<Engine::WallComponent>();   // Dodato da bi mogli majmuni (enemies) izbegavati obstacles

					entityManager->AddEntity(std::move(obstacle));
				}

				m_currentLevelNo = LevelNumber::LEVEL_THREE;
				entityManager->AddEntity(std::move(obstacle));
			}
		}
	}

	bool ObstacleController::ShutDown()
	{
		return true;
	}
}