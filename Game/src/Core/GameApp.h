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
    class ObstacleController;
	class HudController;
    class StageController;
    class AudioSystem;
    class PauseController;


    class GameApp final : public Engine::Application
    {
	public:
        bool m_wasPaused{false};
        bool isPaused{false};
		int m_window_width{ 1280 };
		int m_window_height{ 720 };
		bool m_WasThereAResize{ false };
        bool m_IsTitleScreen{ true };
    private:
        void GameSpecificWindowData() override;
        bool GameSpecificInit() override;
        void GameSpecificUpdate(float dt) override;
        bool GameSpecificShutdown() override;		
		void setWindowSize(int win_width, int win_height) override;

		void LoadTextures();

		std::unique_ptr<CameraController> m_CameraController{};
		std::unique_ptr<PlayerController> m_PlayerController{};
        std::unique_ptr<ObstacleController> m_ObstacleController{};
        std::unique_ptr<BorderController> m_BorderController{};
		std::unique_ptr<HudController> m_HudController{};
        std::unique_ptr<StageController> m_StageController{};
        std::unique_ptr<AudioSystem> m_AudioSystem{};
        std::unique_ptr<PauseController> m_PauseSystem{};
		//std::unique_ptr<DummyController> m_DummyController{};
        std::unique_ptr<EnemiesFactory> m_Factory{};
    };

}

Engine::Application* Engine::CreateApplication()
{
    return new Game::GameApp();
}
