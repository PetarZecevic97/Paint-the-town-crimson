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
		void Update(float dt, Engine::EntityManager* entityManager, Engine::TextureManager* textureManager, bool isGameOver);
		bool ShutDown();
	private:
		LevelNumber m_currentLevelNo;
		int m_height;
		int m_width;
		Engine::Texture* m_texture;
	};
}