#pragma once
#include "Misc.h"

namespace Engine
{
	class EntityManager;
	class TextureManager;
	struct Texture;
}

namespace Game
{
	class ObstacleController
	{
	public:
		bool Init(Engine::EntityManager* entityManager, Engine::Texture* texture, LevelNumber levelNo, int width, int height);
		void Update(float dt, Engine::EntityManager* entityManager);
		bool ShutDown();
	private:
	};
}