#pragma once

#include <vector>

#include "Entities/NPC/EnemySpecificEntities.h"
#include "Entities/NPC/Controllers/FireNPCController.h"
#include "Entities/NPC/Controllers/WaterNPCController.h"
#include "Entities/NPC/Controllers/WindNPCController.h"
#include "Entities/NPC/Controllers/EarthNPCController.h"

#define MAX_ENEMIES 50

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
		bool IsFactoryPaused() const { return m_Pause; }
		void Sleep();
	private:

		void SpawnNextNPC(Engine::EntityManager* entityManager, Engine::TextureManager* texture);

		std::unique_ptr<WaterNPCController> m_WaterNPCController;
		std::unique_ptr<FireNPCController> m_FireNPCController;
		std::unique_ptr<WindNPCController> m_WindNPCController;
		std::unique_ptr<EarthNPCController> m_EarthNPCController;
		int m_CurrentElement = 1;
		float m_Delta = 0.f;
		float m_Width, m_Height;
		std::vector<vec2> m_SpawnPositions{};
		float m_SpawnTimer = 2.f;
		const int m_Levels[3] = { 1, 3, 100 };
		int m_CurrentLevel = 0;
		int m_SpawnFrequency = 5;
		bool m_Pause = false;
		unsigned int m_SleepTimeStart = 0;

	};


}