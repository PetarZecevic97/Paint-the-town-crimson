#pragma once


namespace Engine
{

}

namespace Game
{
	class EarthNPCController
	{
	public:
		bool Init(Engine::EntityManager* entityManager, Engine::Texture* textureManager, vec2 spawnPosition);
		void Update(float dt, Engine::EntityManager* entityManager);
		bool ShutDown();
	private:
	};
}