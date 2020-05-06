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
        stage->AddComponent<Engine::ObstacleComponent>();

        entityManager_->AddEntity(std::move(stage));

        return true;
    }
}