#include "precomp.h"
#include "PlayerController.h"

namespace Game
{

    bool CreateItem(Engine::EntityManager* entityManager_, int item_type, Engine::Texture* texture, Engine::Entity* npc) {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to ProjectileController::Init()");

        auto item = std::make_unique<Engine::Entity>();
        auto npc_trans = npc->GetComponent<Engine::TransformComponent>();
        float x = npc_trans->m_Position[0];
        float y = npc_trans->m_Position[1];

        item->AddComponent<Engine::TransformComponent>(x, y, 22.f, 22.f);
        item->AddComponent<Engine::CollisionComponent>(22.f, 22.f);
        item->AddComponent<Engine::ItemComponent>(SDL_GetTicks());
        item->AddComponent<Engine::SpriteComponent>().m_Image = texture;

        SDL_Rect new_rect;
        switch (item_type) {
        case 0:
            new_rect = { 0, 0, 18, 12 };
            break;
        default:
            new_rect = { 0, 0, 18, 12 };
            break;
        }
        //Slicing up a spritesheet and taking what is ours
        auto* comp = item->GetComponent<Engine::SpriteComponent>();
        comp->m_src = new_rect;
        //if we want to animate an entity
        comp->m_Animation = true;

        entityManager_->AddEntity(std::move(item));


        return !(entityManager_->GetAllEntitiesWithComponent<Engine::ItemComponent>().empty());
    }

    void UpdateItems(Engine::EntityManager* entityManager_) {

        auto items = entityManager_->GetAllEntitiesWithComponents<Engine::ItemComponent>();

        for (auto& item : items)
        {


            if (SDL_GetTicks() > item->GetComponent<Engine::ItemComponent>()->m_timeCreated + 8000) {
                entityManager_->RemoveEntity(item->GetId());
                continue;
            }

            auto collider = item->GetComponent<Engine::CollisionComponent>();


            for (const auto& entity : collider->m_CollidedWith)
            {
                if (entity->HasComponent<Engine::PlayerComponent>())
                {
                    entityManager_->RemoveEntity(item->GetId());
                    break;
                }
            }

        }

    }

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

        //Slicing up a spritesheet and taking what is ours
        auto* comp = fireball->GetComponent<Engine::SpriteComponent>();
        SDL_Rect new_rect{ 50, 0, 11, 11 };
        comp->m_src = new_rect;
        //if we want to animate an entity
        comp->m_Animation = true;

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

    void UpdateFireballs(Engine::EntityManager* entityManager_) {

        auto entitiesToMove = entityManager_->GetAllEntitiesWithComponents<Engine::FireballComponent>();

        for (auto& fireball : entitiesToMove)
        {

            auto* sprite = fireball->GetComponent<Engine::SpriteComponent>();

            int ticks = (SDL_GetTicks() / 200) % 4;

            SDL_Rect new_rect{ 50 + (12 * ticks), 0, 11, 11 };
            sprite->m_src = new_rect;

            auto collider = fireball->GetComponent<Engine::CollisionComponent>();

            for (auto* entity : collider->m_CollidedWith)
            {
                if (entity->HasComponent<Engine::NPCComponent>())
                {
                   CreateItem(entityManager_, 0, fireball->GetComponent<Engine::SpriteComponent>()->m_Image, entity);
                   entityManager_->RemoveEntity(fireball->GetId());
                   entityManager_->RemoveEntity(entity->GetId());
                   
                   break;

                }

                if (entity->HasComponent<Engine::BorderComponent>())
                {
                    entityManager_->RemoveEntity(fireball->GetId());
                    break;
                }
            }

            

        }

    }

    bool PlayerController::Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to PlayerController::Init()");
        ASSERT(texture_ != nullptr, "Must pass valid pointer to texture to PlayerController::Init()");

        
        auto player = std::make_unique<Engine::Entity>();

        player->AddComponent<Engine::TransformComponent>(0.f, 0.f, 100.f, 100.f);
        player->AddComponent<Engine::CollisionComponent>(100.f, 100.f);
        player->AddComponent<Engine::PlayerComponent>();
        player->AddComponent<Engine::InputComponent>();
        player->AddComponent<Engine::MoverComponent>();
        player->AddComponent<Engine::SpriteComponent>().m_Image = texture_;
		
		//Slicing up a spritesheet and taking what is ours
		auto *comp = player->GetComponent<Engine::SpriteComponent>();
		SDL_Rect new_rect{ 50, 50, 50, 50 };
		comp->m_src = new_rect;
		//if we want to animate an entity
		comp->m_Animation = true;

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

        for (auto& player : entitiesToMove)
        {
            auto move = player->GetComponent<Engine::MoverComponent>();
            auto transform = player->GetComponent<Engine::TransformComponent>();
            auto input = player->GetComponent<Engine::InputComponent>();
            auto speed = 200.f; // entity->GetComponent<Engine::PlayerComponent>()->m_PanSpeed;

            bool moveUpInput = Engine::InputManager::IsActionActive(input, "PlayerMoveUp");
            bool moveDownInput = Engine::InputManager::IsActionActive(input, "PlayerMoveDown");
            bool moveLeftInput = Engine::InputManager::IsActionActive(input, "PlayerMoveLeft");
            bool moveRightInput = Engine::InputManager::IsActionActive(input, "PlayerMoveRight");

            bool shootUpInput = Engine::InputManager::IsActionActive(input, "PlayerShootUp");
            bool shootDownInput = Engine::InputManager::IsActionActive(input, "PlayerShootDown");
            bool shootLeftInput = Engine::InputManager::IsActionActive(input, "PlayerShootLeft");
            bool shootRightInput = Engine::InputManager::IsActionActive(input, "PlayerShootRight");

            int ticks = SDL_GetTicks() - m_last_fired_time;
            if (ticks > m_fireball_cooldown && (shootUpInput || shootDownInput || shootLeftInput || shootRightInput)) {
                m_last_fired_time += ticks;
                Game::CreateFireball(entityManager_);
            }
            
            move->m_TranslationSpeed.y = speed * ((moveUpInput ? -1.0f : 0.0f) + (moveDownInput ? 1.0f : 0.0f));
            move->m_TranslationSpeed.x = speed * ((moveLeftInput ? -1.0f : 0.0f) + (moveRightInput ? 1.0f : 0.0f));

			//Idle Animation 

            auto* comp = player->GetComponent<Engine::SpriteComponent>();
			if (!(moveUpInput || moveDownInput || moveLeftInput || moveRightInput)) {
				int ticks = (SDL_GetTicks() / 200) % 5;

				SDL_Rect new_rect{ 50 * ticks, 50, 50, 50 };
				comp->m_src = new_rect;
			}else if (moveRightInput) {
				int ticks = (SDL_GetTicks() / 200) % 6;

				SDL_Rect new_rect{ 50 * ticks, 100, 50, 50 };
				comp->m_src = new_rect;
			}else if (moveLeftInput) {
				int ticks = (SDL_GetTicks() / 200) % 6;

				SDL_Rect new_rect{ 300 - 50 * ticks, 150, 50, 50 };
				comp->m_src = new_rect;
			}else if (moveDownInput) {
				int ticks = (SDL_GetTicks() / 200) % 4;

				SDL_Rect new_rect{ 50 * ticks, 200, 50, 50 };
				comp->m_src = new_rect;
			}else if (moveUpInput) {
				int ticks = (SDL_GetTicks() / 200) % 4;

				SDL_Rect new_rect{ 50 * ticks, 250, 50, 50 };
				comp->m_src = new_rect;
			}


            auto collider = player->GetComponent<Engine::CollisionComponent>();

            for (const auto& entity : collider->m_CollidedWith)
            {
                if (entity->HasComponent<Engine::BorderComponent>())
                {
                    move->m_TranslationSpeed.y = speed * ((moveUpInput ? 20.0f : 0.0f) + (moveDownInput ? -20.0f : 0.0f));
                    move->m_TranslationSpeed.x = speed * ((moveLeftInput ? 20.0f : 0.0f) + (moveRightInput ? -20.0f : 0.0f));
                }
            }
        
        }

        UpdateFireballs(entityManager_);
    }
}
