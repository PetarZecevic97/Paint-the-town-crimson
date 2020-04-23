#include "precomp.h"
#include "Window.h"

#include <SDL.h>

namespace Engine
{
    bool Window::Init(const WindowData& windowData_)
    {
        LOG_INFO("Initializing Window");

        m_WindowData = windowData_;
        ASSERT(m_WindowData.m_Width > 0 && m_WindowData.m_Height > 0, "Window size must be greater than zero");

        m_NativeWindowHandle = SDL_CreateWindow(
            m_WindowData.m_Title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            m_WindowData.m_Width,
            m_WindowData.m_Height,
            0
        );

        if (m_NativeWindowHandle == nullptr)
        {
            LOG_CRITICAL("Unable to create a window. SDL Error: {}", SDL_GetError());
            return false;
        }

        LOG_INFO("Window successfully initialized");
        return true;
    }

    bool Window::Shutdown()
    {
        LOG_INFO("Shutting down Window");

        if (m_NativeWindowHandle != nullptr)
        {
            SDL_DestroyWindow(m_NativeWindowHandle);
        }

        m_NativeWindowHandle = nullptr;

        return true;
    }

    Window::~Window()
    {
        Shutdown();
    }
}
