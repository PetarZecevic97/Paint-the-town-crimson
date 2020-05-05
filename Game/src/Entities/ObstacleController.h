#pragma once


namespace Engine
{
	class EntityManager;
	class TextureManager;
	class Texture;
}

namespace Game
{
	class ObstacleController
	{
	public:
		bool Init(Engine::EntityManager* entityManager, Engine::Texture* texture, int numberOfObstacles)
		void Update(float dt, Engine::EntityManager* entityManager);
		bool ShutDown();
	private:
	};
}