#pragma once

namespace Engine
{
	class EntityManager;

	class NPCSystem
	{
	public:
		bool Init();
		void Update(float dt, EntityManager* entityManager);
	private:
	};
}