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
    m_RenderSystem->SetBackgroundColor(148, 0, 211, 1);

	LoadTextures();

	m_CameraController = std::make_unique<CameraController>();
	m_CameraController->Init(m_EntityManager.get());

    m_PlayerController = std::make_unique<PlayerController>();
    //m_PlayerController->Init(m_EntityManager.get(), m_TextureManager->GetTexture("wizard"));
	m_PlayerController->Init(m_EntityManager.get(), m_TextureManager->GetTexture("mage"));


	m_EnemyController = std::make_unique<EnemyController>();
	m_EnemyController->Init(m_EntityManager.get(), m_TextureManager->GetTexture("enemy"));

	//m_DummyController = std::make_unique<DummyController>();
	//m_DummyController->Init(m_EntityManager.get(), m_TextureManager->GetTexture("dummy"));

    return true;
}

void Game::GameApp::GameSpecificUpdate(float dt)
{
    m_PlayerController->Update(dt, m_EntityManager.get());
}

bool Game::GameApp::GameSpecificShutdown()
{
    return true;
}

void Game::GameApp::LoadTextures()
{
	auto renderer = m_RenderSystem->GetRenderer();
	m_TextureManager->CreateTexture(renderer, "enemy", "Data/enemy.jpg");
	m_TextureManager->CreateTexture(renderer, "dummy", "Data/dummy.jpg");
	//wizard is an old and haggard texture, with mage_3 everyone is gonna be like: Wizard WHO?
	m_TextureManager->CreateTexture(renderer, "wizard", "Data/wizard.png");
	m_TextureManager->CreateTexture(renderer, "mage", "Data/mage_3.png");
}