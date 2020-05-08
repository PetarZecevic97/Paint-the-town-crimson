#pragma once

#include <precomp.h>

namespace Game
{
	bool CreateFireball(Engine::EntityManager* entityManager_, int direction, int direction2);
	void UpdateFireballs(Engine::EntityManager* entityManager_);
}
