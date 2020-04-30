#include "precomp.h"
#include "BorderController.h"



namespace Game
{
    bool BorderController::Init(Engine::EntityManager* entityManager_, int window_width, int window_height, Engine::Texture* texture)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to BorderController::Init()");

        // Left
        auto border = std::make_unique<Engine::Entity>();

        border->AddComponent<Engine::BorderComponent>();
        border->AddComponent<Engine::TransformComponent>(-window_width * 1.0 / 2, 0.f, 1.f, window_height * 1.0);
        border->AddComponent<Engine::CollisionComponent>(1.f, window_height*1.0);
        border->AddComponent<Engine::SpriteComponent>().m_Image = texture;

        entityManager_->AddEntity(std::move(border));

        // Right
        border = std::make_unique<Engine::Entity>();

        border->AddComponent<Engine::BorderComponent>();
        border->AddComponent<Engine::TransformComponent>(window_width * 1.0 / 2, 0.f, 1.f, window_height * 1.0);
        border->AddComponent<Engine::CollisionComponent>(1.f, window_height * 1.0);
        border->AddComponent<Engine::SpriteComponent>().m_Image = texture;

        entityManager_->AddEntity(std::move(border));

        // Down
        border = std::make_unique<Engine::Entity>();

        border->AddComponent<Engine::BorderComponent>();
        border->AddComponent<Engine::TransformComponent>(0.f, window_height * 1.0 / 2, window_width * 1.0, 1.f);
        border->AddComponent<Engine::CollisionComponent>(window_width * 1.0, 1.f);
        border->AddComponent<Engine::SpriteComponent>().m_Image = texture;

        entityManager_->AddEntity(std::move(border));

        // Up
        border = std::make_unique<Engine::Entity>();

        border->AddComponent<Engine::BorderComponent>();
        border->AddComponent<Engine::TransformComponent>(0.f, -window_height * 1.0 / 2, window_width * 1.0, 1.f);
        border->AddComponent<Engine::CollisionComponent>(window_width * 1.0, 1.f);
        border->AddComponent<Engine::SpriteComponent>().m_Image = texture;

        entityManager_->AddEntity(std::move(border));

        return true;
    }
}