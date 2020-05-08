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
        SDL_Rect new_rect = { 0, 0, 1240, 720 };
        sprite->m_src = new_rect;
        sprite->m_Animation = true;

        stage->AddComponent<Engine::TransformComponent>(60, 0, 1152.f, 720.f);
        //stage->AddComponent<Engine::ObstacleComponent>();
        stage->AddComponent<Engine::LevelComponent>();

        entityManager_->AddEntity(std::move(stage));
        m_currentLevelNo = LevelNumber::LEVEL_ONE;

        return true;
    }

    void StageController::Update(Engine::EntityManager* entityManager_, int window_width, int window_height,bool isGameOver_) 
    {
        auto stages = entityManager_->GetAllEntitiesWithComponent< Engine::LevelComponent>();


        if (!stages.empty())
        {

            auto stage = entityManager_->GetAllEntitiesWithComponent< Engine::LevelComponent>()[0];
            auto* sprite = stage->GetComponent<Engine::SpriteComponent>();

            if (isGameOver_)
            {
                SDL_Rect new_rect = { 0, 720 * 3, 1240, 720 };
                sprite->m_src = new_rect;
                LevelNumber::LEVEL_GAME_OVER;
            }
            else if (m_currentLevelNo == LevelNumber::LEVEL_ONE)
            {
                SDL_Rect new_rect = { 0, 720, 1240, 720 };
                sprite->m_src = new_rect;
                m_currentLevelNo = LevelNumber::LEVEL_TWO;
            }
            else if (m_currentLevelNo == LevelNumber::LEVEL_TWO)
            {
                SDL_Rect new_rect = { 0, 720 * 2, 1240, 720 };
                sprite->m_src = new_rect;
                m_currentLevelNo = LevelNumber::LEVEL_THREE;
            }
            else if (m_currentLevelNo == LevelNumber::LEVEL_THREE)
            {
                SDL_Rect new_rect = { 0, 720 * 4 + 50, 1240, 720 };
                sprite->m_src = new_rect;
                m_currentLevelNo = LevelNumber::LEVEL_WIN;
            }
        }
    }
}