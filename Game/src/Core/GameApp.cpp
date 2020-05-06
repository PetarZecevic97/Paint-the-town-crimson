#include "precomp.h"

#include "GameApp.h"

#include "Entities/PlayerController.h"
#include "Entities/CameraController.h"
#include "Entities/BorderController.h"

#include <Engine.h>
#include <Core/EntryPoint.h>
#include "Entities/CameraController.h"
#include "Entities/ObstacleController.h"
#include "Entities/NPC/EnemyController.h"
#include "Entities/NPC/EnemiesFactory.h"
#include "Entities/Dummy/DummyController.h"

void Game::GameApp::GameSpecificWindowData()
{
    Engine::WindowData gameSpecificWindowData;
    gameSpecificWindowData.m_Title = "Magemaggedon";
    gameSpecificWindowData.m_Width = m_window_width;
    gameSpecificWindowData.m_Height = m_window_height;
    // gameSpecificWindowData.m_Vsync = true;
    SetWindowData(gameSpecificWindowData);
}

bool Game::GameApp::GameSpecificInit()
{
    m_RenderSystem->SetBackgroundColor(148, 0, 211, 1);

	LoadTextures();
	//here we try to get the correct window height and width upon entry
	int w, h;
	SDL_GetRendererOutputSize(m_RenderSystem->GetRenderer()->GetNativeRenderer(), &w, &h);
	setWindowSize(w, h);

	m_CameraController = std::make_unique<CameraController>();
	m_CameraController->Init(m_EntityManager.get());

    m_PlayerController = std::make_unique<PlayerController>();
    //m_PlayerController->Init(m_EntityManager.get(), m_TextureManager->GetTexture("wizard"));
	m_PlayerController->Init(m_EntityManager.get(), m_TextureManager->GetTexture("mage"));

	//m_DummyController = std::make_unique<DummyController>();
	//m_DummyController->Init(m_EntityManager.get(), m_TextureManager->GetTexture("dummy"),200.f, 200.f);

    m_Factory = std::make_unique<EnemiesFactory>();
	m_Factory->Init();

	m_ObstacleController = std::make_unique<ObstacleController>();
	m_ObstacleController->Init(m_EntityManager.get(), m_TextureManager->GetTexture("obstacle"), LevelNumber::LEVEL_TWO, m_window_width, m_window_height);

	m_BorderController = std::make_unique<BorderController>();
	m_BorderController->Init(m_EntityManager.get(), m_window_width, m_window_height, m_TextureManager->GetTexture("blank"));


    return true;
}

void Game::GameApp::GameSpecificUpdate(float dt)
{
    m_PlayerController->Update(dt, m_EntityManager.get());
	Game::UpdateItems(m_EntityManager.get());
	if (!m_Factory->IsFactoryPaused())
	{
		m_Factory->Update(dt, m_EntityManager.get(), m_TextureManager.get());
	}
	else
	{
		m_Factory->Sleep();
	}
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
	m_TextureManager->CreateTexture(renderer, "obstacle", "Data/obstacles.png");
	//wizard is an old and haggard texture, with mage_3 everyone is gonna be like: Wizard WHO?
	m_TextureManager->CreateTexture(renderer, "wizard", "Data/wizard.png");

	m_TextureManager->CreateTexture(renderer, "mage", "Data/mage_3.png");
	m_TextureManager->CreateTexture(renderer, "blank", "Data/blank.png");
	m_TextureManager->CreateTexture(renderer, "water", "Data/WaterElemental.png");
	m_TextureManager->CreateTexture(renderer, "fire", "Data/FireElemental.png");
	m_TextureManager->CreateTexture(renderer, "earth", "Data/earth_elemental.png");
	m_TextureManager->CreateTexture(renderer, "wind", "Data/air_elemental.png");
	
}

void Game::GameApp::setWindowSize(int win_width, int win_height) {
	m_window_width = win_width;
	m_window_height = win_height;
}

