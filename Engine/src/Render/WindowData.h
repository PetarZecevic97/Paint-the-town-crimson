#pragma once
#include <string>

constexpr int DEFAULT_WIDTH = 800;
constexpr int DEFAULT_HEIGHT = 600;

namespace Engine
{
    struct WindowData
    {
        std::string m_Title{ "UBISOFT MATF KURS - Default Name" };
        int m_Width{ DEFAULT_WIDTH };
        int m_Height{ DEFAULT_HEIGHT };
        bool m_Vsync{ false };
    };
}
