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

		if (m_Delta > 2.f && m_CurrentElement != MAX_ENEMIES)
		{
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
				m_WindNPCController->Init(entityManager, texture->GetTexture("fire"), m_SpawnPositions[randomPosition]);
				break;
			case 3:
				m_EarthNPCController->Init(entityManager, texture->GetTexture("earth"), m_SpawnPositions[randomPosition]);
				break;
			default:
				ASSERT(randomPosition>3 || randomPosition<0, "Out of range: [0,3]");
			}
			m_CurrentElement++;
		}

		m_WaterNPCController->Update(dt,entityManager);
		m_FireNPCController->Update(dt, entityManager);
		m_WindNPCController->Update(dt, entityManager);
		m_EarthNPCController->Update(dt, entityManager);
		
	}

	void EnemiesFactory::Reset()
	{

	}

	bool EnemiesFactory::ShutDown()
	{
		return true;
	}

}