#pragma once

#include <Core\Application.h>

namespace Game
{
    class CameraController;
    class PlayerController;
	class EnemyController;
	class DummyController;
    class EnemiesFactory;
    class BorderController;


    class GameApp final : public Engine::Application
    {
	public:
		
		int m_window_width{ 1280 };
		int m_window_height{ 720 };
    private:
        void GameSpecificWindowData() override;
        bool GameSpecificInit() override;
        void GameSpecificUpdate(float dt) override;
        bool GameSpecificShutdown() override;
		void setWindowSize(int win_width, int win_height) override;

		void LoadTextures();

		std::unique_ptr<CameraController> m_CameraController{};
		std::unique_ptr<PlayerController> m_PlayerController{};


		//std::unique_ptr<DummyController> m_DummyController{};

        std::unique_ptr<BorderController> m_BorderController{};
        

        std::unique_ptr<EnemiesFactory> m_Factory{};
    };

}

Engine::Application* Engine::CreateApplication()
{
    return new Game::GameApp();
}
