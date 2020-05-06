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
        border->AddComponent<Engine::LeftBorderComponent>();
        border->AddComponent<Engine::TransformComponent>(-static_cast<float>(window_width * 0.8 / 2), 0.f, 1.f, static_cast<float>(window_height));
        border->AddComponent<Engine::CollisionComponent>(1.f, static_cast<float>(window_height));
        border->AddComponent<Engine::SpriteComponent>().m_Image = texture;

        entityManager_->AddEntity(std::move(border));

        // Right
        border = std::make_unique<Engine::Entity>();

        border->AddComponent<Engine::BorderComponent>();
        border->AddComponent<Engine::RightBorderComponent>();
        border->AddComponent<Engine::TransformComponent>(static_cast<float>(window_width / 2), 0.f, 1.f, static_cast<float>(window_height));
        border->AddComponent<Engine::CollisionComponent>(1.f, static_cast<float>(window_height));
        border->AddComponent<Engine::SpriteComponent>().m_Image = texture;

        entityManager_->AddEntity(std::move(border));

        // Down
        border = std::make_unique<Engine::Entity>();

        border->AddComponent<Engine::BorderComponent>();
        border->AddComponent<Engine::BottomBorderComponent>();
        border->AddComponent<Engine::TransformComponent>(0.f, static_cast<float>(window_height / 2), static_cast<float>(window_width), 1.f);
        border->AddComponent<Engine::CollisionComponent>(static_cast<float>(window_width), 1.f);
        border->AddComponent<Engine::SpriteComponent>().m_Image = texture;

        entityManager_->AddEntity(std::move(border));

        // Up
        border = std::make_unique<Engine::Entity>();

        border->AddComponent<Engine::BorderComponent>();
        border->AddComponent<Engine::TopBorderComponent>();
        border->AddComponent<Engine::TransformComponent>(0.f, -static_cast<float>(window_height/ 2), static_cast<float>(window_width), 1.f);
        border->AddComponent<Engine::CollisionComponent>(static_cast<float>(window_width), 1.f);
        border->AddComponent<Engine::SpriteComponent>().m_Image = texture;

        entityManager_->AddEntity(std::move(border));

        return true;
    }

    void BorderController::Update(Engine::EntityManager* entityManager_, int window_width, int window_height)
    {
      auto leftBorder = entityManager_->GetAllEntitiesWithComponents<Engine::LeftBorderComponent>()[0];

      auto leftTransform = leftBorder->GetComponent<Engine::TransformComponent>();
      auto leftCollision = leftBorder->GetComponent<Engine::CollisionComponent>();

      leftTransform->m_Position.x = -static_cast<float>(window_width * 0.8 / 2);
      leftTransform->m_Size.y = static_cast<float>(window_height);
      leftCollision->m_Size.y = static_cast<float>(window_height);

      auto rightBorder = entityManager_->GetAllEntitiesWithComponents<Engine::RightBorderComponent>()[0];

      auto rightTransform = rightBorder->GetComponent<Engine::TransformComponent>();
      auto rightCollision = rightBorder->GetComponent<Engine::CollisionComponent>();

      rightTransform->m_Position.x = static_cast<float>(window_width / 2);
      rightTransform->m_Size.y = static_cast<float>(window_height);
      rightCollision->m_Size.y = static_cast<float>(window_height);

      auto topBorder = entityManager_->GetAllEntitiesWithComponents<Engine::TopBorderComponent>()[0];

      auto topTransform = topBorder->GetComponent<Engine::TransformComponent>();
      auto topCollision = topBorder->GetComponent<Engine::CollisionComponent>();

      topTransform->m_Position.y = -static_cast<float>(window_height / 2);
      topTransform->m_Size.x = static_cast<float>(window_width);
      topCollision->m_Size.x = static_cast<float>(window_width);

      auto bottomBorder = entityManager_->GetAllEntitiesWithComponents<Engine::BottomBorderComponent>()[0];

      auto bottomTransform = bottomBorder->GetComponent<Engine::TransformComponent>();
      auto bottomCollision = bottomBorder->GetComponent<Engine::CollisionComponent>();

      bottomTransform->m_Position.y = static_cast<float>(window_height / 2);
      bottomTransform->m_Size.x = static_cast<float>(window_width);
      bottomCollision->m_Size.x = static_cast<float>(window_width);

      
     
       
    }
}