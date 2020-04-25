#pragma once

namespace Engine
{
	class EntityManager;
	class TextureManager;
}

namespace Game
{
	class DummyController
	{
	public:
		bool Init(Engine::EntityManager* entityManager, Engine::Texture* texture);
		void Update(float dt, Engine::EntityManager* entityManager);
	};

}