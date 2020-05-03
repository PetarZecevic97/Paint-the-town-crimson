#pragma once

#define MAX_ENEMIES 10
#include <vector>
#include "Entities/NPC/EnemySpecificEntities.h"
#include "WaterNPCController.h"

namespace Engine
{
	class Entity;
	class EntityManager;
	class TextureManager;
}

namespace Game
{
	class EnemyController;
	class WaterNPCController;

	class EnemiesFactory
	{
	public:
		bool Init();
		void Update(float dt, Engine::EntityManager* entitymanager, Engine::TextureManager* texture);
		void Reset();
		bool ShutDown();
	private:
		//std::vector<EnemyController*> m_Enemies{};
		std::unique_ptr<WaterNPCController> m_WaterNPCController;
		int m_CurrentElement = 0;
		float m_Delta = 0.f;
		float m_Width, m_Height;
		std::vector<vec2> m_SpawnPositions{};

	};


}