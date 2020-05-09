#include "precomp.h"

#include "GameApp.h"

#include "Entities/PlayerController.h"
#include "Entities/CameraController.h"
#include "Entities/BorderController.h"
#include "Entities/HudController.h"

#include <Engine.h>
#include <Core/EntryPoint.h>
#include "Entities/CameraController.h"
#include "Entities/ObstacleController.h"
#include "Entities/NPC/EnemyController.h"
#include "Entities/NPC/EnemiesFactory.h"
#include "Entities/Dummy/DummyController.h"
#include "Entities/StageController.h"
#include "Entities/ItemsController.h"
#include "Entities/AudioController.h"
#include "AudioSystem.h"

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

	m_StageController = std::make_unique<StageController>();
	m_StageController->Init(m_EntityManager.get(), m_window_width, m_window_height, m_TextureManager->GetTexture("stage"));

    m_PlayerController = std::make_unique<PlayerController>();
    //m_PlayerController->Init(m_EntityManager.get(), m_TextureManager->GetTexture("wizard"));
	m_PlayerController->Init(m_EntityManager.get(), m_TextureManager->GetTexture("mage"));

	//m_DummyController = std::make_unique<DummyController>();
	//m_DummyController->Init(m_EntityManager.get(), m_TextureManager->GetTexture("dummy"),200.f, 200.f);

    m_Factory = std::make_unique<EnemiesFactory>();
	m_Factory->Init();

	

	m_BorderController = std::make_unique<BorderController>();
	m_BorderController->Init(m_EntityManager.get(), m_window_width, m_window_height, m_TextureManager->GetTexture("blank"));

	m_HudController = std::make_unique<HudController>();
	m_HudController->Init(m_EntityManager.get(), m_TextureManager.get(), m_window_width, m_window_height);


	m_ObstacleController = std::make_unique<ObstacleController>();
	m_ObstacleController->Init(m_EntityManager.get(), m_TextureManager->GetTexture("obstacle"), LevelNumber::LEVEL_TWO, m_window_width, m_window_height);

	auto item_sprite = std::make_unique<Engine::Entity>();
	item_sprite->AddComponent<Engine::SpriteComponent>().m_Image = m_TextureManager->GetTexture("items");
	item_sprite->AddComponent<Engine::ItemStashComponent>();
	m_EntityManager.get()->AddEntity(std::move(item_sprite));

	

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		LOG_CRITICAL("Unable to initialize SDL audio. SDL error: {}", Mix_GetError());
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG_CRITICAL("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	Mix_Music* music = NULL;

	//Load music
	music = Mix_LoadMUS("Data/love_wolf.wav");
	if (music == NULL)
	{
		LOG_CRITICAL("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}
	Mix_PlayMusic(music, -1);

	m_AudioSystem.get()->Init();
	m_AudioSystem.get()->LoadMusic("Data/beat.wav", "background");
	m_AudioSystem.get()->PlayBackgroundMusic("background");

    return true;
}

void Game::GameApp::GameSpecificUpdate(float dt)
{
	Game::UpdateItems(m_EntityManager.get(), m_TextureManager->GetTexture("explosion"));

	if (m_EntityManager.get()->GetAllEntitiesWithComponent<Engine::PlayerComponent>()[0]->GetComponent<Engine::PlayerComponent>()->m_number_of_lives == 0)
	{
		m_Factory->ShutDown(m_EntityManager.get());
		m_StageController->Update(m_EntityManager.get(), m_window_width, m_window_height, true);
		m_ObstacleController->Update(dt, m_EntityManager.get(), m_TextureManager.get(), true);
	}
	else if (!m_Factory->IsFactoryPaused())
	{
		m_Factory->Update(dt, m_EntityManager.get(), m_TextureManager.get());
	}
	else
	{
		if (!m_Factory->Sleep())
		{
			// Sada se ovde vrsi ovde prebacivanje na sledeci nivo ukoliko je player ubio sve neprijatelje
			m_ObstacleController->Update(dt, m_EntityManager.get(), m_TextureManager.get(),false);
			m_StageController->Update(m_EntityManager.get(), m_window_width, m_window_height, false);
		}
	}

	SDL_Event event{ };

	while (SDL_PollEvent(&event) != 0)
	{

		if (event.type == SDL_WINDOWEVENT &&
			event.window.event == SDL_WINDOWEVENT_RESIZED)
		{
			
			m_BorderController->Update(m_EntityManager.get(), event.window.data1, event.window.data2);
			setWindowSize(event.window.data1, event.window.data2);
			m_WasThereAResize = true;
			
		}
		else {
			m_WasThereAResize = false;
		}
		

	}
	m_HudController->Update(m_EntityManager.get(), m_TextureManager.get(), m_window_width, m_window_height, m_WasThereAResize);
	
	m_PlayerController->Update(dt, m_EntityManager.get());
	
	Game::UpdateFireballs(m_EntityManager.get());

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
	m_TextureManager->CreateTexture(renderer, "unblank", "Data/UnBlank.png");
	m_TextureManager->CreateTexture(renderer, "water", "Data/WaterElemental.png");
	m_TextureManager->CreateTexture(renderer, "fire", "Data/FireElemental.png");
	m_TextureManager->CreateTexture(renderer, "earth", "Data/earth_elemental.png");
	m_TextureManager->CreateTexture(renderer, "wind", "Data/air_elemental.png");
	m_TextureManager->CreateTexture(renderer, "stage", "Data/all_stages.png");
	m_TextureManager->CreateTexture(renderer, "items", "Data/items.png");
	m_TextureManager->CreateTexture(renderer, "faded", "Data/faded.png");
	m_TextureManager->CreateTexture(renderer, "numbers", "Data/numbers.png");
	m_TextureManager->CreateTexture(renderer, "slab", "Data/slab.png");
	m_TextureManager->CreateTexture(renderer, "explosion", "Data/explosion-4.png");
	
	
}

void Game::GameApp::setWindowSize(int win_width, int win_height) {
	m_window_width = win_width;
	m_window_height = win_height;
}
