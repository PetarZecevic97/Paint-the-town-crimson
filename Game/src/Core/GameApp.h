#pragma once

#include <Core\Application.h>

namespace Game
{


    class GameApp final : public Engine::Application
    {
    private:
        void GameSpecificWindowData() override;
        bool GameSpecificInit() override;
        void GameSpecificUpdate(float dt) override;
        bool GameSpecificShutdown() override;

    };

}

Engine::Application* Engine::CreateApplication()
{
    return new Game::GameApp();
}
