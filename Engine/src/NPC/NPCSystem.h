#pragma once

namespace Engine
{
	class EntityManager;
	class Entity;

	class NPCSystem
	{
	public:
		bool Init();
		void Update(float dt, EntityManager* entityManager);
	private:
		bool CheckRayCasting(Entity* npc, double angle, std::vector<Entity*>& possibleCooliders);
	};
}