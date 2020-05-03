#include "precomp.h"

#include "EnemiesFactory.h"
#include "WaterNPCController.h"

namespace Game
{
	bool EnemiesFactory::Init()
	{

		m_WaterNPCController = std::make_unique<WaterNPCController>();

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
				m_WaterNPCController->Init(entityManager, texture->GetTexture("enemy"), m_SpawnPositions[randomPosition]);
				break;
			default:
				m_WaterNPCController->Init(entityManager, texture->GetTexture("enemy"),m_SpawnPositions[randomPosition]);
			}
			m_CurrentElement++;

			//if (auto enemy = m_Enemies[m_CurrentElement] )
			//{

			//	//enemy->AddComponent<EnemyComponent>(type);
			//	//enemy->AddComponent<Engine::NPCComponent>();
			//	//enemy->AddComponent<Engine::TransformComponent>(m_SpawnPositions[randomPosition].x, m_SpawnPositions[randomPosition].y, 50.f, 50.f);
			//	//enemy->AddComponent<Engine::CollisionComponent>(50.f, 50.f);
			//	//enemy->AddComponent<Engine::MoverComponent>();
			//	//enemy->AddComponent<Engine::SpriteComponent>().m_Image = texture;
			//	//entityManager->AddEntity(std::move(enemy));
			//}
			//m_Enemies[m_CurrentElement] = nullptr;

		}

		m_WaterNPCController->Update(dt,entityManager);
		
	}

	void EnemiesFactory::Reset()
	{

	}

	bool EnemiesFactory::ShutDown()
	{
		return true;
	}

}