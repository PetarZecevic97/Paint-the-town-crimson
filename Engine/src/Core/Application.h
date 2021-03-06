#pragma once

#include "Render/WindowData.h"

namespace Engine {

    class RenderSystem;
    class PhysicsSystem;
	class NPCSystem;
    class InputManager;
    class EntityManager;
    class TextureManager;
    class AudioSystem;

    class Application
    {
    public:
        bool Init();
        int Run();
        bool Shutdown();
		bool m_Pause{ false };

        virtual ~Application();
        Application() = default;

    protected:
        void SetWindowData(const WindowData& windowData_) { m_WindowData = windowData_; }

        bool m_Running{ false };
        bool m_Reset{ false };

        WindowData m_WindowData{};
        std::unique_ptr<RenderSystem> m_RenderSystem{};
        std::unique_ptr<PhysicsSystem> m_PhysicsSystem{};
        std::unique_ptr<InputManager> m_InputManager{};
        std::unique_ptr<EntityManager> m_EntityManager{};
        std::unique_ptr<TextureManager> m_TextureManager{};
        std::unique_ptr<AudioSystem> m_AudioSystem{};
		std::unique_ptr<NPCSystem> m_NPCSystem{};
        

    private:
        // To be overridden by the game
        virtual void GameSpecificWindowData() = 0;
        virtual bool GameSpecificInit() = 0;
        virtual bool GameSpecificShutdown() = 0;
        virtual void GameSpecificUpdate(float dt) = 0;
		virtual void setWindowSize(int win_width, int win_height) = 0;

        void Update(float dt);

        Application(const Application& other) = delete;
        Application& operator=(Application& other) = delete;
    };

    // To be defined in the game
    Application* CreateApplication();
}
