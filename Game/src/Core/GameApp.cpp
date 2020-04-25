#include "precomp.h"

#include "GameApp.h"

#include "Entities/PlayerController.h"
#include "Entities/CameraController.h"

#include <Engine.h>
#include <Core/EntryPoint.h>
#include "Entities/CameraController.h"
#include "Entities/NPC/EnemyController.h"
#include "Entities/Dummy/DummyController.h"

void Game::GameApp::GameSpecificWindowData()
{
    Engine::WindowData gameSpecificWindowData;
    gameSpecificWindowData.m_Title = "Magemaggedon";
    gameSpecificWindowData.m_Width = 1280;
    gameSpecificWindowData.m_Height = 720;
    // gameSpecificWindowData.m_Vsync = true;
    SetWindowData(gameSpecificWindowData);
}

bool Game::GameApp::GameSpecificInit()
{
    m_RenderSystem->SetBackgroundColor(0, 0, 0, 1);

	m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "blank", "hello_world.jpg");
	m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "dummy", "recourses/dummy.jpg");

	m_CameraController = std::make_unique<CameraController>();
	m_CameraController->Init(m_EntityManager.get());

	m_EnemyController = std::make_unique<EnemyController>();
	m_EnemyController->Init(m_EntityManager.get(), m_TextureManager->GetTexture("blank"));
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "wizard", "../../../Data/wizard.png");

    m_PlayerController = std::make_unique<PlayerController>();
    m_PlayerController->Init(m_EntityManager.get(), m_TextureManager->GetTexture("wizard"));


	m_DummyController = std::make_unique<DummyController>();
	m_DummyController->Init(m_EntityManager.get(), m_TextureManager->GetTexture("dummy"));

    return true;
}

void Game::GameApp::GameSpecificUpdate(float dt)
{
    m_PlayerController->Update(dt, m_EntityManager.get());
	m_EnemyController->Update(dt, m_EntityManager.get());
	m_DummyController->Update(dt, m_EntityManager.get());
}

bool Game::GameApp::GameSpecificShutdown()
{
    return true;
}
