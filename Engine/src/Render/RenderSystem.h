#pragma once
#include "Render/WindowData.h"

namespace Engine
{
    struct WindowData;
    class Renderer;
    class Entity;
    class EntityManager;

    class RenderSystem
    {
    public:
        bool Init(const WindowData& windowData_ = WindowData());
        bool Shutdown();
        void Update(float dt_, EntityManager* entityManager);
        Renderer* GetRenderer();
        void SetBackgroundColor(unsigned char bgR_, unsigned char bgG_, unsigned char bgB_, unsigned char bgA_);
        void SetBackgroundColor(const Color& col_);

        RenderSystem() = default;
    private:
        std::unique_ptr<Renderer> m_Renderer;

        RenderSystem(const RenderSystem& other) = delete;
        RenderSystem& operator=(RenderSystem& other) = delete;
    };
}
