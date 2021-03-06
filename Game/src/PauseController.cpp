#include "precomp.h"
#include "PauseController.h"

namespace Game
{

    bool PauseController::Init(Engine::EntityManager* entityManager_, int window_width, int window_height, Engine::Texture* texture_)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to BorderController::Init()");
        auto overlay = std::make_unique<Engine::Entity>();


        overlay->AddComponent<Engine::SpriteComponent>(100).m_Image = texture_;
        auto* sprite = overlay->GetComponent<Engine::SpriteComponent>();
        SDL_Rect new_rect = { 0, 0, 1240, 720 };
        sprite->m_src = new_rect;
        sprite->m_Animation = true;

        overlay->AddComponent<Engine::TransformComponent>(64.f, 0.f, 1.f, 0.f);
        overlay->AddComponent<Engine::PauseComponent>();
        overlay->AddComponent<Engine::InputComponent>();

        auto inputComp = overlay->GetComponent<Engine::InputComponent>();

        inputComp->inputActions.push_back({ "PauseGame" });
        inputComp->inputActions.push_back({ "Quit" });
        inputComp->inputActions.push_back({ "Reset" });
        
        entityManager_->AddEntity(std::move(overlay));

        return true;
    }

    bool PauseController::Update(Engine::EntityManager* entityManager_, int window_width, int window_height, Engine::Texture* texture_, AudioSystem* audioSystem_, bool justPaused)
    {

        auto overlay = entityManager_->GetAllEntitiesWithComponent<Engine::PauseComponent>()[0];
        auto transform = overlay->GetComponent<Engine::TransformComponent>();
        auto inputComp = overlay->GetComponent<Engine::InputComponent>();
        bool justPressed = Engine::InputManager::WasJustPressed(inputComp, "PauseGame");
        
        


        auto localx = transform->m_Position.x;
        if (true)
        {
            if (localx == 51) 
            {
                transform->m_Position.x = 2000;
                return false;
            }
            else 
            {
                transform->m_Position.x = 51;
                return true;
            }
        }
        return transform->m_Position.x == 51;


    }

    bool PauseController::ShouldExit(Engine::EntityManager* entityManager_)
    {
        auto overlay = entityManager_->GetAllEntitiesWithComponent<Engine::PauseComponent>()[0];
        auto inputComp = overlay->GetComponent<Engine::InputComponent>();
        bool exit = Engine::InputManager::WasJustPressed(inputComp, "Quit");
        return exit;
    }

    bool PauseController::ShouldReset(Engine::EntityManager* entityManager_)
    {
        auto overlay = entityManager_->GetAllEntitiesWithComponent<Engine::PauseComponent>()[0];
        auto inputComp = overlay->GetComponent<Engine::InputComponent>();
        bool reset = Engine::InputManager::WasJustPressed(inputComp, "Reset");
        return reset;
    }

}

