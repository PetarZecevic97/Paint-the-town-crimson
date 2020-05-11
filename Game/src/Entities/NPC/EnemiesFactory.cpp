#include "precomp.h"

#include "EnemiesFactory.h"
#include <stdlib.h>


namespace Game
{
	bool EnemiesFactory::Init()
	{

		m_WaterNPCController = std::make_unique<WaterNPCController>();
		m_FireNPCController = std::make_unique<FireNPCController>();
		m_WindNPCController = std::make_unique<WindNPCController>();
		m_EarthNPCController = std::make_unique<EarthNPCController>();
		m_MentalNPCController = std::make_unique<MentalNPCController>();

		m_Width = 1280;
		m_Height = 720;

		m_SpawnPositions.push_back({ m_Width / 2.0f, 0 });
		m_SpawnPositions.push_back({ -m_Width / 2.0f, 0 });
		m_SpawnPositions.push_back({ 0, m_Height / 2.0f });
		m_SpawnPositions.push_back({ 0, -m_Height / 2.0f });

		srand(static_cast<unsigned int>(time(0)));

		return true;
	}

	void EnemiesFactory::Update(float dt, Engine::EntityManager* entityManager, Engine::TextureManager* texture)
	{
		m_Delta += dt;
		bool exit = m_CurrentElement <= m_Levels[m_CurrentLevel];

		if (m_Delta > m_SpawnTimer && exit)
		{
			SpawnNextNPC(entityManager, texture);
		}
		if (!exit && entityManager->GetAllEntitiesWithComponent<EnemyComponent>().size() == 0)
		{
			m_Pause = true;
			Reset();
			m_SleepTimeStart = SDL_GetTicks();
		}

		m_WaterNPCController->Update(dt, entityManager);
		m_FireNPCController->Update(dt, entityManager);
		m_WindNPCController->Update(dt, entityManager);
		m_EarthNPCController->Update(dt, entityManager);
		m_MentalNPCController->Update(dt, entityManager);

	}

	void EnemiesFactory::Reset()
	{
		m_CurrentElement = 1;
		m_CurrentLevel++;
		m_Delta = 0;
		m_SpawnTimer = 2.f;
		m_SpawnFrequency--;
	}

	void EnemiesFactory::ShutDown(Engine::EntityManager* entityManager)
	{
		auto enemies = entityManager->GetAllEntitiesWithComponents<Engine::NPCComponent>();
		m_CurrentElement = 40;
		m_CurrentLevel = 3;
		for (auto* enemy : enemies) 
		{
			entityManager->RemoveEntity(enemy->GetId());
		}
	}

	bool EnemiesFactory::Sleep()
	{
		if (SDL_GetTicks() - m_SleepTimeStart > 3000 && m_CurrentLevel < 4)
		{
			m_Pause = false;
			return false;
		}
		return true;
	}

	void EnemiesFactory::SpawnNextNPC(Engine::EntityManager* entityManager, Engine::TextureManager* texture)
	{
		m_SpawnTimer -= m_CurrentElement % m_SpawnFrequency == 0 ? (m_SpawnTimer < 0.42f ? 0.f : 0.2f) : 0.f;
		m_Delta = 0.f;

		int enemyType = 4;
		float strongerNPCprobability = static_cast<float>(rand()) / RAND_MAX;
		if (strongerNPCprobability >= 0.7)
		{
			enemyType = rand() % 4;
		}
		
		int rander = rand() % 3;

		int randomPosition = rand() % 4;
		switch (enemyType)
		{
		case 0:
			m_WaterNPCController->Init(entityManager, texture->GetTexture("water"), m_SpawnPositions[randomPosition]);
			break;
		case 1:
			m_FireNPCController->Init(entityManager, texture->GetTexture("fire"), m_SpawnPositions[randomPosition]);
			break;
		case 2:
			m_WindNPCController->Init(entityManager, texture->GetTexture("wind"), m_SpawnPositions[randomPosition]);
			break;
		case 3:
			m_EarthNPCController->Init(entityManager, texture->GetTexture("earth"), m_SpawnPositions[randomPosition]);
			break;
		case 4:
			
			switch (rander) {
			case 0:
				m_MentalNPCController->Init(entityManager, texture->GetTexture("fire_villager"), m_SpawnPositions[randomPosition]);
				break;
			case 1:
				m_MentalNPCController->Init(entityManager, texture->GetTexture("water_villager"), m_SpawnPositions[randomPosition]);
				break;
			case 2:
				m_MentalNPCController->Init(entityManager, texture->GetTexture("wind_villager"), m_SpawnPositions[randomPosition]);
				break;
			default:
				m_MentalNPCController->Init(entityManager, texture->GetTexture("fire_villager"), m_SpawnPositions[randomPosition]);
				break;
			}
			
			break;
		default:
			ASSERT(randomPosition > 4 || randomPosition < 0, "Out of range: [0,4]");
		}
		m_CurrentElement++;
	}
}