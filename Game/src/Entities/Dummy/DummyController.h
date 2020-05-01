#pragma once

namespace Engine
{
	class EntityManager;
	class TextureManager;
}

namespace Game
{
	//Just dummy class,you can use one of these if you need some testing or whatever you need
	//Try not to push it, unless you want to add some improve to it :)

	class DummyController
	{
	public:
		bool Init(Engine::EntityManager* entityManager, Engine::Texture* texture);
		bool Init(Engine::EntityManager* entityManager, Engine::Texture* texture, float position);
		void Update(float dt, Engine::EntityManager* entityManager);
	};

}