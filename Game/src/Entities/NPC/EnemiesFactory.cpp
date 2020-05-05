#include "precomp.h"

#include "EnemiesFactory.h"

namespace Game
{
	bool EnemiesFactory::Init()
	{

		m_WaterNPCController = std::make_unique<WaterNPCController>();
		m_FireNPCController = std::make_unique<FireNPCController>();
		m_WindNPCController = std::make_unique<WindNPCController>();
		m_EarthNPCController = std::make_unique<EarthNPCController>();

		m_Width = 1280;
		m_Height = 720;

		m_SpawnPositions.push_back({ m_Width / 2.0f + 50.0f, 0 });
		m_SpawnPositions.push_back({ -m_Width / 2.0f - 50.0f, 0 });
		m_SpawnPositions.push_back({ 0, m_Height / 2.0f + 50.0f });
		m_SpawnPositions.push_back({ 0, -m_Height / 2.0f - 50.0f });

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

		m_WaterNPCController->Update(dt,entityManager);
		m_FireNPCController->Update(dt, entityManager);
		m_WindNPCController->Update(dt, entityManager);
		m_EarthNPCController->Update(dt, entityManager);
		
	}

	void EnemiesFactory::Reset()
	{
		m_CurrentElement = 1;
		m_CurrentLevel++;
		m_Delta = 0;
		m_SpawnTimer = 2.f;
		m_SpawnFrequency--;
	}

	bool EnemiesFactory::ShutDown()
	{
		return true;
	}

	void EnemiesFactory::Sleep()
	{
		if (SDL_GetTicks() - m_SleepTimeStart > 3000 && m_CurrentLevel<3)
		{
			m_Pause = false;
		}
	}

	void EnemiesFactory::SpawnNextNPC(Engine::EntityManager* entityManager, Engine::TextureManager* texture)
	{
		m_SpawnTimer -= m_CurrentElement % m_SpawnFrequency == 0 ? 0.2f : 0.f;
		m_Delta = 0.f;
		int randomPosition = rand() % 4;
		int enemyType = rand() % 4;
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
		default:
			ASSERT(randomPosition > 3 || randomPosition < 0, "Out of range: [0,3]");
		}
		m_CurrentElement++;
	}
}