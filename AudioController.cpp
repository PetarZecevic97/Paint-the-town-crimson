#pragma once
#include "precomp.h"
#include "AudioController.h"

namespace Game
{

	bool AudioController::Init(Engine::AudioSystem* audioSystem_)
	{
		audioSystem_.init();
	}
	void AudioController::Update(Engine::AudioSystem* audioSystem_)
	{
	}
}