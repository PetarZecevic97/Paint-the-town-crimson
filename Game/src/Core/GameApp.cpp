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
#include "PauseController.h"

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

	// Controllers initialization
	m_CameraController = std::make_unique<CameraController>();
	m_CameraController->Init(m_EntityManager.get());

	// Controller that switches the backdrop from main menu to levels 1,2,3
	m_StageController = std::make_unique<StageController>();
	m_StageController->Init(m_EntityManager.get(), m_window_width, m_window_height, m_TextureManager->GetTexture("stage"));

    m_PlayerController = std::make_unique<PlayerController>();
	m_PlayerController->Init(m_EntityManager.get(), m_TextureManager->GetTexture("mage"));
	
    m_Factory = std::make_unique<EnemiesFactory>();
	m_Factory->Init();

	m_BorderController = std::make_unique<BorderController>();
	m_BorderController->Init(m_EntityManager.get(), m_window_width, m_window_height, m_TextureManager->GetTexture("blank"));

	m_HudController = std::make_unique<HudController>();
	m_HudController->Init(m_EntityManager.get(), m_TextureManager.get(), m_window_width, m_window_height);

	// Controller that generates collidable obstacles like rocks depending on the current level
	m_ObstacleController = std::make_unique<ObstacleController>();
	m_ObstacleController->Init(m_EntityManager.get(), m_TextureManager->GetTexture("obstacle"), m_window_width, m_window_height);

	auto item_sprite = std::make_unique<Engine::Entity>();
	item_sprite->AddComponent<Engine::SpriteComponent>().m_Image = m_TextureManager->GetTexture("items");
	item_sprite->AddComponent<Engine::ItemStashComponent>();
	m_EntityManager.get()->AddEntity(std::move(item_sprite));


	// Controller that handles exiting and pausing the game
	// TODO: Implement game restart
	m_PauseSystem = std::make_unique<PauseController>();
	m_PauseSystem.get()->Init(m_EntityManager.get(), m_window_width, m_window_height,m_TextureManager->GetTexture("pause"));


	// Loading music for all the levels
	m_AudioSystem.get()->LoadMusic("Data/love_wolf.wav", "title");
	m_AudioSystem.get()->LoadMusic("Data/forestLevel.mp3", "level1");
	m_AudioSystem.get()->LoadMusic("Data/fireLevel.mp3", "level2");
	m_AudioSystem.get()->LoadMusic("Data/cloudLevel.mp3", "level3");

	// Loading sound effects
	m_AudioSystem.get()->LoadSoundEffect("Data/pew.wav", "fireball");
	m_AudioSystem.get()->LoadSoundEffect("Data/fireignite.wav", "fireball2");
	m_AudioSystem.get()->LoadSoundEffect("Data/explosion.wav", "explosion");
	m_AudioSystem.get()->LoadSoundEffect("Data/explosion2.wav", "apocalypse");
	m_AudioSystem.get()->LoadSoundEffect("Data/game_over.mp3", "lose");
	m_AudioSystem.get()->LoadSoundEffect("Data/powerup.wav", "powerup");
	m_AudioSystem.get()->LoadSoundEffect("Data/powerup2.wav", "powerup2");
	m_AudioSystem.get()->LoadSoundEffect("Data/win.wav", "win");
	m_AudioSystem.get()->LoadSoundEffect("Data/slam.mp3", "slam");
	m_AudioSystem.get()->LoadSoundEffect("Data/clocktick.wav", "clocktick");
	m_AudioSystem.get()->LoadSoundEffect("Data/YuGiOh.wav", "life");
	m_AudioSystem.get()->LoadSoundEffect("Data/cock.mp3", "cock");
	m_AudioSystem.get()->LoadSoundEffect("Data/speed.wav", "speed");
	m_AudioSystem.get()->LoadSoundEffect("Data/freeze.mp3", "freeze");
	m_AudioSystem.get()->LoadSoundEffect("Data/waterDeath.mp3", "waterDeath");
	m_AudioSystem.get()->LoadSoundEffect("Data/fireDeath.mp3", "fireDeath");
	m_AudioSystem.get()->LoadSoundEffect("Data/smallFireDeath.mp3", "smallFireDeath");
	m_AudioSystem.get()->LoadSoundEffect("Data/rockDeath.mp3", "rockDeath");
	m_AudioSystem.get()->LoadSoundEffect("Data/airDeath.mp3", "airDeath");
	m_AudioSystem.get()->LoadSoundEffect("Data/mentalDeath.mp3", "mentalDeath");
	m_AudioSystem.get()->LoadSoundEffect("Data/wizardHurt.wav", "wizardHurt");
	m_AudioSystem.get()->LoadSoundEffect("Data/wizardDying.wav", "wizardDying");

	// Initializing and configuring start state for sound mixer
	m_AudioSystem.get()->PlayBackgroundMusic("title");
	m_AudioSystem.get()->SetMusicVolume(10);
	m_AudioSystem.get()->SetEffectsVolume(30);

    return true;
}

void Game::GameApp::GameSpecificUpdate(float dt)
{
		// Inherited member vars from Application
		// Used as indicators whether the game should exit or restart
		m_Running = !m_PauseSystem.get()->ShouldExit(m_EntityManager.get());
		m_Reset = m_PauseSystem.get()->ShouldReset(m_EntityManager.get());
		if (!m_IsTitleScreen)
		{
			Game::UpdateItems(m_EntityManager.get(), m_TextureManager->GetTexture("explosion"), m_AudioSystem.get());
			
			// Checks if the mage has lost all of his lives, the condition is <= 0 and not == 0 
			// because in many cases he can lose multiple lives at the same time
			if (m_EntityManager.get()->GetAllEntitiesWithComponent<Engine::PlayerComponent>()[0]->GetComponent<Engine::PlayerComponent>()->m_number_of_lives <= 0)
			{

				m_Factory->ShutDown(m_EntityManager.get());
				m_StageController->Update(m_EntityManager.get(), m_window_width, m_window_height, true, m_AudioSystem.get(), false);
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
					m_ObstacleController->Update(dt, m_EntityManager.get(), m_TextureManager.get(), false);
					m_StageController->Update(m_EntityManager.get(), m_window_width, m_window_height, false, m_AudioSystem.get(), false);
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
			
			m_PlayerController->Update(dt, m_EntityManager.get(), m_AudioSystem.get());

			Game::UpdateFireballs(m_EntityManager.get(), m_AudioSystem.get());
		}
		else
		{
			if (m_IsTitleScreen)
			{
				// Listens for start action (enter) with UpdateIsTitleSceen(), and updates the title screen animation in the meanwhile with Update(). 
				m_IsTitleScreen = !m_StageController.get()->UpdateIsTitleSceen(m_EntityManager.get());
				m_StageController.get()->Update(m_EntityManager.get(), m_window_width, m_window_height, false, m_AudioSystem.get(), m_IsTitleScreen);
			}

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
	m_TextureManager->CreateTexture(renderer, "fire_villager", "Data/villager_fire.png");
	m_TextureManager->CreateTexture(renderer, "water_villager", "Data/water_villager.png");
	m_TextureManager->CreateTexture(renderer, "pause", "Data/pause.png");
	m_TextureManager->CreateTexture(renderer, "wind_villager", "Data/wind_villager.png");
	m_TextureManager->CreateTexture(renderer, "earth_villager", "Data/earth_villager.png");

}

void Game::GameApp::setWindowSize(int win_width, int win_height) {
	m_window_width = win_width;
	m_window_height = win_height;
}
