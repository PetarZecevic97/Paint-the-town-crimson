#pragma once
namespace Engine
{
	class EntityManager;
	class TextureManager;
}

namespace Game
{
	class EnemyController
	{
	public:
		virtual bool Init(Engine::EntityManager* entityManager, Engine::Texture* textureManager); //create spawn points
		virtual void Update(float dt, Engine::EntityManager* entityManager) = 0;
		virtual bool ShotDown() = 0;
	protected:
		//Add spawn points
	};
}
