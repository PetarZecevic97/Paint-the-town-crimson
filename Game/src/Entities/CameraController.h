#pragma once


namespace Engine
{
	class EntityManager;
}

namespace Game
{
	class CameraController
	{
	public:
		bool Init(Engine::EntityManager* entityManager_);
	};
}