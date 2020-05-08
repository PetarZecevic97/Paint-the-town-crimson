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
		
		m_currentLevelNo == levelNo;

		m_height = height;
		m_width = width;
		
		// Wall init
		std::vector < std::pair<int, int> > lObstacleLocations;
		for (int i = 80; i < 1280; i += 50) 
		{
			if (i > 500 && i < 750)continue;
			lObstacleLocations.push_back(std::make_pair(-0.5*width + i, height*0.5-25));
			lObstacleLocations.push_back(std::make_pair(-0.5 * width + i, -height * 0.5+25));
		}
		for (int i = 0; i < 720; i += 50)
		{
			if (i > 250 && i < 550)continue;
			lObstacleLocations.push_back(std::make_pair(0.5 * width-100, -height * 0.5 + i-25));
			lObstacleLocations.push_back(std::make_pair(-0.5 * width+80, -height * 0.5 + i-25));
		}

		for (auto loc : lObstacleLocations)
		{

			auto obstacle = std::make_unique<Engine::Entity>();
			obstacle->AddComponent<Engine::SpriteComponent>().m_Image = texture;
			auto* sprite = obstacle->GetComponent<Engine::SpriteComponent>();
			SDL_Rect new_rect = { 0, 0, 50, 50 };
			sprite->m_src = new_rect;
			sprite->m_Animation = true;

			obstacle->AddComponent<Engine::TransformComponent>(loc.first + 0.06 * m_width, loc.second, 50.f, 50.f);
			obstacle->AddComponent<Engine::CollisionComponent>(50.f, 50.f);
			obstacle->AddComponent<Engine::ObstacleComponent>();
			obstacle->AddComponent<Engine::WallComponent>();   // Dodato da bi mogli majmuni (enemies) izbegavati obstacles

			entityManager->AddEntity(std::move(obstacle));
		}
		
		
		
		return true;
	}

	void ObstacleController::Update(float dt, Engine::EntityManager* entityManager, Engine::TextureManager* textureManager)
	{
		auto obstacles = entityManager->GetAllEntitiesWithComponent<Engine::ObstacleComponent>();
		

		// Delete all Obstacle components
		for (auto obstacle : obstacles)
		{
			if (!obstacle->HasComponent<Engine::WallComponent>() || m_currentLevelNo == LevelNumber::LEVEL_THREE)
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

		if (m_currentLevelNo == LevelNumber::LEVEL_ONE)
		{

			auto obstacle = std::make_unique<Engine::Entity>();
			std::vector < std::pair<int, int> > lObstacleLocations;

			lObstacleLocations.push_back(std::make_pair(0.8 * m_height / 3, 0.8 * m_height / 3 - 60));
			lObstacleLocations.push_back(std::make_pair(0.8 * m_height / 3, 0.8 * m_height / 3 - 120));
			lObstacleLocations.push_back(std::make_pair(0.8 * m_height / 3, 0.8 * m_height / 3));
			lObstacleLocations.push_back(std::make_pair(0.8 * m_height / 3 - 60, 0.8 * m_height / 3));
			lObstacleLocations.push_back(std::make_pair(0.8 * m_height / 3 - 120, 0.8 * m_height / 3));

			lObstacleLocations.push_back(std::make_pair(0.8 * -m_height / 3, 0.8 * m_height / 3 - 60));
			lObstacleLocations.push_back(std::make_pair(0.8 * -m_height / 3, 0.8 * m_height / 3 - 120));
			lObstacleLocations.push_back(std::make_pair(0.8 * -m_height / 3, 0.8 * m_height / 3));
			lObstacleLocations.push_back(std::make_pair(0.8 * -m_height / 3 + 60, 0.8 * m_height / 3));
			lObstacleLocations.push_back(std::make_pair(0.8 * -m_height / 3 + 120, 0.8 * m_height / 3));

			lObstacleLocations.push_back(std::make_pair(0.8 * m_height / 3, 0.8 * -m_height / 3 + 60));
			lObstacleLocations.push_back(std::make_pair(0.8 * m_height / 3, 0.8 * -m_height / 3 + 120));
			lObstacleLocations.push_back(std::make_pair(0.8 * m_height / 3, 0.8 * -m_height / 3));
			lObstacleLocations.push_back(std::make_pair(0.8 * m_height / 3 - 60, 0.8 * -m_height / 3));
			lObstacleLocations.push_back(std::make_pair(0.8 * m_height / 3 - 120, 0.8 * -m_height / 3));

			lObstacleLocations.push_back(std::make_pair(0.8 * -m_height / 3, 0.8 * -m_height / 3 + 60));
			lObstacleLocations.push_back(std::make_pair(0.8 * -m_height / 3, 0.8 * -m_height / 3 + 120));
			lObstacleLocations.push_back(std::make_pair(0.8 * -m_height / 3, 0.8 * -m_height / 3));
			lObstacleLocations.push_back(std::make_pair(0.8 * -m_height / 3 + 60, 0.8 * -m_height / 3));
			lObstacleLocations.push_back(std::make_pair(0.8 * -m_height / 3 + 120, 0.8 * -m_height / 3));


			for (auto loc : lObstacleLocations)
			{

				auto obstacle = std::make_unique<Engine::Entity>();
				obstacle->AddComponent<Engine::SpriteComponent>().m_Image = textureManager->GetTexture("obstacle");
				auto* sprite = obstacle->GetComponent<Engine::SpriteComponent>();
				SDL_Rect new_rect = { 0, 50, 50, 50 };
				sprite->m_src = new_rect;
				sprite->m_Animation = true;

				obstacle->AddComponent<Engine::TransformComponent>(loc.first + 0.06 * m_width, loc.second, 50.f, 50.f);
				obstacle->AddComponent<Engine::CollisionComponent>(50.f, 50.f);
				obstacle->AddComponent<Engine::ObstacleComponent>();
				//obstacle->AddComponent<Engine::WallComponent>();   // Dodato da bi mogli majmuni (enemies) izbegavati obstacles

				entityManager->AddEntity(std::move(obstacle));
			}
			m_currentLevelNo = LevelNumber::LEVEL_TWO;
			entityManager->AddEntity(std::move(obstacle));
		}
		else if (m_currentLevelNo == LevelNumber::LEVEL_TWO)
		{
			auto obstacle = std::make_unique<Engine::Entity>();

			std::vector < std::pair<int, int> > lObstacleLocations;
			lObstacleLocations.push_back(std::make_pair(0.8 * m_height / 4, 0));
			lObstacleLocations.push_back(std::make_pair(-0.8 * m_height / 4, 0));
			lObstacleLocations.push_back(std::make_pair(0, 0.8 * m_height / 4));
			lObstacleLocations.push_back(std::make_pair(0, -0.8 * m_height / 4));
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
				obstacle->AddComponent<Engine::WallComponent>();   // Dodato da bi mogli majmuni (enemies) izbegavati obstacles

				entityManager->AddEntity(std::move(obstacle));
			}

			m_currentLevelNo = LevelNumber::LEVEL_THREE;
			entityManager->AddEntity(std::move(obstacle));
		}


	}

	bool ObstacleController::ShutDown()
	{
		return true;
	}
}