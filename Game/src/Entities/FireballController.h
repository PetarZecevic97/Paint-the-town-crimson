#pragma once

#include <precomp.h>
#include "Audio System/AudioSystem.h"

namespace Game
{
	bool CreateFireball(Engine::EntityManager* entityManager_, int direction, int direction2);
	void UpdateFireballs(Engine::EntityManager* entityManager_, Engine::AudioSystem * audioSystem_);
}
