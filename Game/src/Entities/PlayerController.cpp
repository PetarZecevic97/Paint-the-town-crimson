#include "precomp.h"
#include "PlayerController.h"

namespace Game
{

    bool CreateFireball(Engine::EntityManager* entityManager_) {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to ProjectileController::Init()");

        auto player = entityManager_->GetAllEntitiesWithComponent< Engine::PlayerComponent>()[0];

        auto fireball = std::make_unique<Engine::Entity>();
        auto player_trans = player->GetComponent<Engine::TransformComponent>();
        float x = player_trans->m_Position[0];
        float y = player_trans->m_Position[1];

        fireball->AddComponent<Engine::TransformComponent>(x, y, 22.f, 22.f);
        fireball->AddComponent<Engine::CollisionComponent>(22.f, 22.f);
        fireball->AddComponent<Engine::FireballComponent>();
        fireball->AddComponent<Engine::MoverComponent>();
        //mage firing mages yaaay
        fireball->AddComponent<Engine::SpriteComponent>().m_Image = player->GetComponent<Engine::SpriteComponent>()->m_Image;

        auto input = player->GetComponent<Engine::InputComponent>();

        bool shootUpInput = Engine::InputManager::IsActionActive(input, "PlayerShootUp");
        bool shootDownInput = Engine::InputManager::IsActionActive(input, "PlayerShootDown");
        bool shootLeftInput = Engine::InputManager::IsActionActive(input, "PlayerShootLeft");
        bool shootRightInput = Engine::InputManager::IsActionActive(input, "PlayerShootRight");

        float speed = 300.f;

        if (shootUpInput) {
            auto move = fireball->GetComponent<Engine::MoverComponent>();
            move->m_TranslationSpeed.y = -speed;
        }
        else if (shootDownInput) {
            auto move = fireball->GetComponent<Engine::MoverComponent>();
            move->m_TranslationSpeed.y = speed;
        }

        if (shootLeftInput) {
            auto move = fireball->GetComponent<Engine::MoverComponent>();
            move->m_TranslationSpeed.x = -speed;
        }
        else  if (shootRightInput) {
            auto move = fireball->GetComponent<Engine::MoverComponent>();
            move->m_TranslationSpeed.x = speed;
        }

        entityManager_->AddEntity(std::move(fireball));


        return !(entityManager_->GetAllEntitiesWithComponent<Engine::FireballComponent>().empty());
    }

    bool PlayerController::Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to PlayerController::Init()");
        ASSERT(texture_ != nullptr, "Must pass valid pointer to texture to PlayerController::Init()");

        
        auto player = std::make_unique<Engine::Entity>();

        player->AddComponent<Engine::TransformComponent>(0.f, 0.f, 75.f, 75.f);
        player->AddComponent<Engine::CollisionComponent>(75.f, 75.f);
        player->AddComponent<Engine::PlayerComponent>();
        player->AddComponent<Engine::InputComponent>();
        player->AddComponent<Engine::MoverComponent>();
        player->AddComponent<Engine::SpriteComponent>().m_Image = texture_;

        auto inputComp = player->GetComponent<Engine::InputComponent>();

        inputComp->inputActions.push_back({ "PlayerMoveUp" });
        inputComp->inputActions.push_back({ "PlayerMoveDown" });
        inputComp->inputActions.push_back({ "PlayerMoveLeft" });
        inputComp->inputActions.push_back({ "PlayerMoveRight" });

        inputComp->inputActions.push_back({ "PlayerShootUp" });
        inputComp->inputActions.push_back({ "PlayerShootDown" });
        inputComp->inputActions.push_back({ "PlayerShootLeft" });
        inputComp->inputActions.push_back({ "PlayerShootRight" });

        entityManager_->AddEntity(std::move(player));
        

        return !(entityManager_->GetAllEntitiesWithComponent<Engine::PlayerComponent>().empty());
    }

    void PlayerController::Update(float dt, Engine::EntityManager* entityManager_)
    {
        auto entitiesToMove = entityManager_->GetAllEntitiesWithComponents<Engine::PlayerComponent, Engine::MoverComponent, Engine::InputComponent>();

        for (auto& entity : entitiesToMove)
        {
            auto move = entity->GetComponent<Engine::MoverComponent>();
            auto input = entity->GetComponent<Engine::InputComponent>();
            auto speed = 200.f; // entity->GetComponent<Engine::PlayerComponent>()->m_PanSpeed;

            bool moveUpInput = Engine::InputManager::IsActionActive(input, "PlayerMoveUp");
            bool moveDownInput = Engine::InputManager::IsActionActive(input, "PlayerMoveDown");
            bool moveLeftInput = Engine::InputManager::IsActionActive(input, "PlayerMoveLeft");
            bool moveRightInput = Engine::InputManager::IsActionActive(input, "PlayerMoveRight");

            bool shootUpInput = Engine::InputManager::IsActionActive(input, "PlayerShootUp");
            bool shootDownInput = Engine::InputManager::IsActionActive(input, "PlayerShootDown");
            bool shootLeftInput = Engine::InputManager::IsActionActive(input, "PlayerShootLeft");
            bool shootRightInput = Engine::InputManager::IsActionActive(input, "PlayerShootRight");


            if (shootUpInput || shootDownInput || shootLeftInput || shootRightInput) {
                Game::CreateFireball(entityManager_);
            }

            move->m_TranslationSpeed.y = speed * ((moveUpInput ? -1.0f : 0.0f) + (moveDownInput ? 1.0f : 0.0f));
            move->m_TranslationSpeed.x = speed * ((moveLeftInput ? -1.0f : 0.0f) + (moveRightInput ? 1.0f : 0.0f));


        
        }
    }
}
