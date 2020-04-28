#include "precomp.h"

#include "EnemiesFactory.h"

namespace Game
{
	bool EnemiesFactory::Init()
	{
		m_Enemies = std::vector<Engine::Entity*>(MAX_ENEMIES);
		for(int i =0;i<MAX_ENEMIES;i++)
		{
			m_Enemies[i] = new Engine::Entity();
		}
		return true;
	}

	void EnemiesFactory::Update(float dt, Engine::EntityManager* entityManager, EnemyType type, Engine::Texture* texture)
	{
		m_Delta += dt;
		if (m_Delta > 2.f && m_CurrentElement != MAX_ENEMIES)
		{
			m_Delta = 0.f;

			if (auto enemy = m_Enemies[m_CurrentElement] )
			{
				enemy->AddComponent<EnemyComponent>(type);
				enemy->AddComponent<Engine::NPCComponent>();
				enemy->AddComponent<Engine::TransformComponent>(300.f, 300.f, 50.f, 50.f);
				enemy->AddComponent<Engine::CollisionComponent>(50.f, 50.f);
				enemy->AddComponent<Engine::MoverComponent>();
				enemy->AddComponent<Engine::SpriteComponent>().m_Image = texture;
				entityManager->AddEntity(std::move(enemy));
			}
			m_Enemies[m_CurrentElement] = nullptr;
			m_CurrentElement++;
		}
		
	}

	void EnemiesFactory::Reset()
	{

	}

	bool EnemiesFactory::ShutDown()
	{
		return true;
	}

}