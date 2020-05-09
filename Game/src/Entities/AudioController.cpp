#pragma once
#include "precomp.h"
#include "../Engine/AudioSystem.h"
#include "AudioController.h"

namespace Game 
{
	bool AudioController::Init(Engine::AudioSystem* audioSystem_) 
	{
		audioSystem_->Init();
		audioSystem_->LoadMusic("Data/beat.wav", "background");
		audioSystem_->PlayBackgroundMusic("background");
		
	}
	void AudioController::Update(Engine::AudioSystem* audioSystem_) 
	{

	}
}