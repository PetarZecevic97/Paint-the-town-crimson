#pragma once
#include "../Engine/AudioSystem.h"

namespace Game
{
    class AudioController
    {
    public:
        bool Init(Engine::AudioSystem* audioSystem_);
        void Update(Engine::AudioSystem* audioSystem_);
    
    };
}
