#pragma once

namespace Engine
{
	class EntityManager;
	class TextureManager;
}

namespace Game
{
	class HudController
	{
	public:
		bool Init(Engine::EntityManager* entityManager_, Engine::TextureManager* texture_manager_, int window_width, int window_height);
		void Update(Engine::EntityManager* entityManager_, Engine::TextureManager* texture_manager_, int window_width, int window_height, bool onResize);
	};

}
