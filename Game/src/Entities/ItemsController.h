#pragma once
#include <precomp.h>

namespace Game
{

	bool CreateItem(Engine::EntityManager* entityManager_, int item_type, Engine::Texture* texture, Engine::Entity* npc);
	void UpdateItems(Engine::EntityManager* entityManager_);
}
