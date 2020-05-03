#pragma once

#include <vector>

#include "Entities/NPC/EnemySpecificEntities.h"
#include "Entities/NPC/Controllers/FireNPCController.h"
#include "Entities/NPC/Controllers/WaterNPCController.h"
#include "Entities/NPC/Controllers/WindNPCController.h"
#include "Entities/NPC/Controllers/EarthNPCController.h"

#define MAX_ENEMIES 10

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
	class FireNPCController;
	class WindNPCController;
	class EarthNPCController;

	class EnemiesFactory
	{
	public:
		bool Init();
		void Update(float dt, Engine::EntityManager* entitymanager, Engine::TextureManager* texture);
		void Reset();
		bool ShutDown();
	private:
		std::unique_ptr<WaterNPCController> m_WaterNPCController;
		std::unique_ptr<FireNPCController> m_FireNPCController;
		std::unique_ptr<WindNPCController> m_WindNPCController;
		std::unique_ptr<EarthNPCController> m_EarthNPCController;
		int m_CurrentElement = 0;
		float m_Delta = 0.f;
		float m_Width, m_Height;
		std::vector<vec2> m_SpawnPositions{};

	};


}