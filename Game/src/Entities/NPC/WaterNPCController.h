#pragma once

#include "EnemyController.h"

namespace Engine
{
	class EntityManager;
	class TextureManager;
}

namespace Game
{
	class WaterNPCController
	{
	public:
		bool Init(Engine::EntityManager* entityManager, Engine::Texture* textureManager,vec2 spawnPosition);
		void Update(float dt, Engine::EntityManager* entityManager);
		bool ShutDown();
	private:
	};

}

