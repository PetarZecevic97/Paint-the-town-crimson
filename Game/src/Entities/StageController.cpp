#include "precomp.h"
#include "StageController.h"


namespace Game
{
    bool StageController::Init(Engine::EntityManager* entityManager_, int window_width, int window_height, Engine::Texture* texture)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to BorderController::Init()");

        auto stage = std::make_unique<Engine::Entity>();
        stage->AddComponent<Engine::SpriteComponent>().m_Image = texture;
        auto* sprite = stage->GetComponent<Engine::SpriteComponent>();
        SDL_Rect new_rect = { 0, 720*5, 1240, 720 };
        sprite->m_src = new_rect;
        sprite->m_Animation = true;

        stage->AddComponent<Engine::TransformComponent>(60.f, 0.f, 1200.f, 730.f);
        stage->AddComponent<Engine::LevelComponent>();
        stage->AddComponent<Engine::InputComponent>();

        auto inputComp = stage->GetComponent<Engine::InputComponent>();

        inputComp->inputActions.push_back({ "Start" });

        entityManager_->AddEntity(std::move(stage));
        m_currentLevelNo = LevelNumber::LEVEL_MENU;

        return true;
    }

    void StageController::Update(Engine::EntityManager* entityManager_, int window_width, int window_height,bool isGameOver_, Engine::AudioSystem * audioSystem_, bool isTitleScreen) 
    {
        auto stages = entityManager_->GetAllEntitiesWithComponent< Engine::LevelComponent>();


        if (!stages.empty())
        {

            auto stage = entityManager_->GetAllEntitiesWithComponent< Engine::LevelComponent>()[0];
            auto* sprite = stage->GetComponent<Engine::SpriteComponent>();

            if (isGameOver_ && m_currentLevelNo != LevelNumber::LEVEL_GAME_OVER)
            {
                SDL_Rect new_rect = { 0, 720 * 3, 1280, 710 };
                sprite->m_src = new_rect;
                audioSystem_->StopMusic();
                audioSystem_->PlaySoundEffect("lose");
                m_currentLevelNo = LevelNumber::LEVEL_GAME_OVER;
                
            }
            else if (m_currentLevelNo == LevelNumber::LEVEL_MENU) 
            {
                if (isTitleScreen) 
                {
                    auto obstacles = entityManager_->GetAllEntitiesWithComponent<Engine::ObstacleComponent>();


                    // Delete all Obstacle components
                    for (auto obstacle : obstacles)
                    {
                        obstacle->GetComponent<Engine::TransformComponent>()->m_Size.x = 1;
                        obstacle->GetComponent<Engine::TransformComponent>()->m_Size.y = 1;
                    }
                    int ticks = (SDL_GetTicks() / 400) % 2;

                    SDL_Rect new_rect = { 0, 720 * 5+(735*ticks), 1240, 720 };
                    sprite->m_src = new_rect;
                }
                else
                {
                    auto obstacles = entityManager_->GetAllEntitiesWithComponent<Engine::ObstacleComponent>();


                    // Delete all Obstacle components
                    for (auto obstacle : obstacles)
                    {
                        obstacle->GetComponent<Engine::TransformComponent>()->m_Size.x = 50;
                        obstacle->GetComponent<Engine::TransformComponent>()->m_Size.y = 50;
                    }

                    SDL_Rect new_rect = { 0, 0, 1280, 720 };
                    sprite->m_src = new_rect;
                    audioSystem_->PlayBackgroundMusic("level1");
                    m_currentLevelNo = LevelNumber::LEVEL_ONE;
                }
                
            }
            else if (m_currentLevelNo == LevelNumber::LEVEL_ONE)
            {
                SDL_Rect new_rect = { 0, 720, 1240, 720 };
                sprite->m_src = new_rect;
                audioSystem_->PlayBackgroundMusic("level2");
                m_currentLevelNo = LevelNumber::LEVEL_TWO;
                
            }
            else if (m_currentLevelNo == LevelNumber::LEVEL_TWO)
            {
                SDL_Rect new_rect = { 0, 720 * 2, 1240, 720 };
                sprite->m_src = new_rect;
                audioSystem_->PlayBackgroundMusic("level3");
                m_currentLevelNo = LevelNumber::LEVEL_THREE;
                
            }
            else if (m_currentLevelNo == LevelNumber::LEVEL_THREE)
            {
                SDL_Rect new_rect = { 0, 720 * 4, 1240, 720 };
                sprite->m_src = new_rect;
                audioSystem_->StopMusic();
                audioSystem_->PlaySoundEffect("win");
                m_currentLevelNo = LevelNumber::LEVEL_WIN;
            }

            //Svaki put kad se level promeni, player se postavlja na sredinu i unistavaju se svi itemi
            auto player = entityManager_->GetAllEntitiesWithComponent<Engine::PlayerComponent>()[0];
            player->GetComponent<Engine::TransformComponent>()->m_Position.x = 64.f;
            player->GetComponent<Engine::TransformComponent>()->m_Position.y = 0.f;
            auto items = entityManager_->GetAllEntitiesWithComponent<Engine::ItemComponent>();
            for (const auto& item : items)
            {
                entityManager_->RemoveEntity(item->GetId());
            }
        }
    }
}