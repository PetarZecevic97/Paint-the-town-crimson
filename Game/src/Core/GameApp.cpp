#include "precomp.h"

#include "GameApp.h"

#include <Engine.h>
#include <Core/EntryPoint.h>


void Game::GameApp::GameSpecificWindowData()
{
    Engine::WindowData gameSpecificWindowData;
    gameSpecificWindowData.m_Title = "Nikola's Pong";
    gameSpecificWindowData.m_Width = 1280;
    gameSpecificWindowData.m_Height = 720;
    // gameSpecificWindowData.m_Vsync = true;
    SetWindowData(gameSpecificWindowData);
}

bool Game::GameApp::GameSpecificInit()
{
    m_RenderSystem->SetBackgroundColor(0, 0, 0, 1);


    return true;
}

void Game::GameApp::GameSpecificUpdate(float dt)
{
}

bool Game::GameApp::GameSpecificShutdown()
{
    return true;
}
