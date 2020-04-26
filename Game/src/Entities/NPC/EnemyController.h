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
		bool Init(Engine::EntityManager* entityManager, Engine::Texture* textureManager);
		void Update(float dt, Engine::EntityManager* entityManager);
	};
}
