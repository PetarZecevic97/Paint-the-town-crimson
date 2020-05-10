#pragma once
#include <precomp.h>
#include "Audio System/AudioSystem.h"

namespace Game
{

	bool CreateItem(Engine::EntityManager* entityManager_, int item_type, Engine::Texture* texture, Engine::Entity* npc);
	void UpdateItems(Engine::EntityManager* entityManager_, Engine::Texture* texture, AudioSystem* audioSystem_);
	void CreateExplosion(Engine::EntityManager* entityManager_, Engine::Texture* texture, AudioSystem* audioSystem_);
	void UpdateExplosion(Engine::EntityManager* entityManager_, AudioSystem* audioSystem_);
}
