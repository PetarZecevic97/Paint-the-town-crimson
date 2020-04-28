#pragma once

#define MAX_ENEMIES (10)
#include <vector>
#include "Entities/NPC/EnemySpecificEntities.h"

namespace Engine
{
	class Entity;
	class EntityManager;
}

namespace Game
{
	class EnemiesFactory
	{
	public:
		bool Init();
		void Update(float dt, Engine::EntityManager* entitymanager, EnemyType type, Engine::Texture* texture);
		void Reset();
		bool ShutDown();
	private:
		std::vector<Engine::Entity*> m_Enemies{};
		int m_CurrentElement = 0;
		float m_Delta = 0.f;
	};


}