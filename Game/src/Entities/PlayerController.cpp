#include "precomp.h"
#include "PlayerController.h"
#include "FireballController.h"


namespace Game
{

    bool PlayerController::Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to PlayerController::Init()");
        ASSERT(texture_ != nullptr, "Must pass valid pointer to texture to PlayerController::Init()");

        
        auto player = std::make_unique<Engine::Entity>();

        player->AddComponent<Engine::TransformComponent>(0.f, 0.f, 50.f, 50.f);
        player->AddComponent<Engine::CollisionComponent>(50.f, 50.f);
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

    void PlayerController::Update(float dt, Engine::EntityManager* entityManager_, AudioSystem* audioSystem_)
    {
        auto entitiesToMove = entityManager_->GetAllEntitiesWithComponents<Engine::PlayerComponent, Engine::MoverComponent, Engine::InputComponent>();
		
        for (auto& player : entitiesToMove)
        {
            auto move = player->GetComponent<Engine::MoverComponent>();
            auto transform = player->GetComponent<Engine::TransformComponent>();
            auto input = player->GetComponent<Engine::InputComponent>();
            auto speed = player->GetComponent<Engine::PlayerComponent>()->m_speed;
            //auto speed = 200.f; // entity->GetComponent<Engine::PlayerComponent>()->m_PanSpeed;

            bool moveUpInput = Engine::InputManager::IsActionActive(input, "PlayerMoveUp");
            bool moveDownInput = Engine::InputManager::IsActionActive(input, "PlayerMoveDown");
            bool moveLeftInput = Engine::InputManager::IsActionActive(input, "PlayerMoveLeft");
            bool moveRightInput = Engine::InputManager::IsActionActive(input, "PlayerMoveRight");

            bool shootUpInput = Engine::InputManager::IsActionActive(input, "PlayerShootUp");
            bool shootDownInput = Engine::InputManager::IsActionActive(input, "PlayerShootDown");
            bool shootLeftInput = Engine::InputManager::IsActionActive(input, "PlayerShootLeft");
            bool shootRightInput = Engine::InputManager::IsActionActive(input, "PlayerShootRight");

			if (moveLeftInput && moveRightInput) {
				moveLeftInput = false;
				moveRightInput = false;
			}

			if (moveUpInput && moveDownInput) {
				moveUpInput = false;
				moveDownInput = false;
			}
			
            int ticks = SDL_GetTicks() - m_last_fired_time;
            if (ticks > player->GetComponent<Engine::PlayerComponent>()->m_fireballCooldown && (shootUpInput || shootDownInput || shootLeftInput || shootRightInput)) {
                m_last_fired_time += ticks;
                int limit = 1;
                if (player->GetComponent<Engine::PlayerComponent>()->m_multishotBuff)
                {
                    limit = 8;
                }
				audioSystem_->PlaySoundEffect("fireball");
                for (int i = 1; i <= limit; i++)
				{
                    Game::CreateFireball(entityManager_, 0, i);
					
                    if (player->GetComponent<Engine::PlayerComponent>()->m_tripleshotBuff)
                    {
                        Game::CreateFireball(entityManager_, 1, i);
                        Game::CreateFireball(entityManager_, 2, i);
                    }
                }
                
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
			//ovo je mozda problem - ako je entyty koji removojemo u ovome
            for (auto* entity : collider->m_CollidedWith)
            {
				if (entity != nullptr) {

					
					if (entity->GetId() > 10000000) {
						continue;
					}
					if (entity->HasComponent<Engine::BorderComponent>()) {

						move->m_TranslationSpeed.y = 0;
						move->m_TranslationSpeed.x = 0;

						auto ent_transform = entity->GetComponent<Engine::TransformComponent>();
						float ent_left_edge = ent_transform->m_Position.x + ent_transform->m_Size.x / 2 + transform->m_Size.x / 2;
						float ent_right_edge = ent_transform->m_Position.x - ent_transform->m_Size.x / 2 - transform->m_Size.x / 2;
						float ent_up_edge = ent_transform->m_Position.y - ent_transform->m_Size.y / 2 - transform->m_Size.y / 2;
						float ent_down_edge = ent_transform->m_Position.y + ent_transform->m_Size.y / 2 + transform->m_Size.y / 2;

						if (entity->HasComponent<Engine::TopBorderComponent>()) {
							transform->m_Position.y = ent_down_edge + 10;
						}
						else if (entity->HasComponent<Engine::BottomBorderComponent>()) {
							transform->m_Position.y = ent_up_edge - 10;
						}
						else if (entity->HasComponent<Engine::LeftBorderComponent>()) {
							transform->m_Position.x = ent_left_edge + 10;
						}
						else if (entity->HasComponent<Engine::RightBorderComponent>()) {
							transform->m_Position.x = ent_right_edge - 10;
						}
						
					}

					if (entity->HasComponent<Engine::ObstacleComponent>())
					{
						audioSystem_->PlaySoundEffect("slam");
						move->m_TranslationSpeed.y = 0;
						move->m_TranslationSpeed.x = 0;

						auto ent_transform = entity->GetComponent<Engine::TransformComponent>();
						float ent_left_edge = ent_transform->m_Position.x - ent_transform->m_Size.x / 2;
						float ent_right_edge = ent_transform->m_Position.x + ent_transform->m_Size.x / 2;
						float ent_up_edge = ent_transform->m_Position.y - ent_transform->m_Size.y / 2;
						float ent_down_edge = ent_transform->m_Position.y + ent_transform->m_Size.y / 2;


						if (transform->m_Position.x > ent_right_edge) {
							transform->m_Position.x = ent_right_edge + 10.f + transform->m_Size.x / 2;
						}else if (transform->m_Position.x < ent_left_edge) {
							transform->m_Position.x = ent_left_edge - 10.f - transform->m_Size.x / 2;
						}else if (transform->m_Position.y > ent_down_edge) {
							transform->m_Position.y = ent_down_edge + 10.f + transform->m_Size.y / 2;
						}
						else if (transform->m_Position.y < ent_up_edge) {
							transform->m_Position.y = ent_up_edge - 10.f - transform->m_Size.y / 2;
						}

					}
					 if (entity->HasComponent<Engine::NPCComponent>())
					{
						audioSystem_->PlaySoundEffect("slam");
                        entityManager_->RemoveEntity(entity->GetId());
						player->GetComponent<Engine::PlayerComponent>()->m_number_of_lives--;

                        // Ovaj if je prakticno prebacen u GameApp, za sada je da kad player umre, samo se iscrta stage Game Over,
                        // mozemo se dogovoriti oko tacnih detalja
						/*if (player->GetComponent<Engine::PlayerComponent>()->m_number_of_lives == 0) {
							player->GetComponent<Engine::TransformComponent>()->m_Position.x = 0.f;
							player->GetComponent<Engine::TransformComponent>()->m_Position.y = 0.f;
							player->GetComponent<Engine::PlayerComponent>()->m_number_of_lives = 3;
							auto enemies = entityManager_->GetAllEntitiesWithComponents<Engine::NPCComponent>();
							for (auto* enemy : enemies) {
								entityManager_->RemoveEntity(enemy->GetId());
							}
							break;
						}*/
					}
				}


            }
        
        }

    }
}
