#include "FireballController.h"
#include "ItemsController.h"
#include <stdlib.h>
#include <time.h>

#include "Entities/NPC/EnemySpecificEntities.h"

namespace Game
{
	// Here we can clearly see how the fireballs get created
	bool CreateFireball(Engine::EntityManager* entityManager_, int direction, int direction2) {
		ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to ProjectileController::Init()");

		auto player = entityManager_->GetAllEntitiesWithComponent< Engine::PlayerComponent>()[0];

		auto fireball = std::make_unique<Engine::Entity>();
		auto player_trans = player->GetComponent<Engine::TransformComponent>();
		float x = player_trans->m_Position[0];
		float y = player_trans->m_Position[1];
		auto input = player->GetComponent<Engine::InputComponent>();
		
		// A fireball originates from the center of the mage - i wanted to move it so it gets fired from the flame
		// but it makes the aiming weird
		fireball->AddComponent<Engine::TransformComponent>(x, y, 18.f, 18.f);
		fireball->AddComponent<Engine::CollisionComponent>(18.f, 18.f);
		fireball->AddComponent<Engine::FireballComponent>();
		fireball->AddComponent<Engine::MoverComponent>();
		// Mage firing mages yaaay - this is when we had only one spritesheet and no fireballs :D
		fireball->AddComponent<Engine::SpriteComponent>().m_Image = player->GetComponent<Engine::SpriteComponent>()->m_Image;

		auto* comp = fireball->GetComponent<Engine::SpriteComponent>();
		SDL_Rect new_rect{ 50, 0, 11, 11 };
		comp->m_src = new_rect;
		comp->m_Animation = true;

		float speed = 300.f;

		bool shootUpInput = false;
		bool shootDownInput = false;
		bool shootLeftInput = false;
		bool shootRightInput = false;

		// this is for the multishot item - direction2 indicates the direction of the fireball - this fires in every direction 
		if (player->GetComponent<Engine::PlayerComponent>()->m_multishotBuff)
		{
			switch (direction2) {
			case 1:
				shootUpInput = true;
				break;
			case 2:
				shootUpInput = true;
				shootRightInput = true;
				speed /= 1.41421; //so it fires them in a circle shape - calculations by Zeka
				break;
			case 3:
				shootRightInput = true;
				break;
			case 4:
				shootRightInput = true;
				shootDownInput = true;
				speed /= 1.41421;
				break;
			case 5:
				shootDownInput = true;
				break;
			case 6:
				shootDownInput = true;
				shootLeftInput = true;
				speed /= 1.41421;
				break;
			case 7:
				shootLeftInput = true;
				break;
			case 8:
				shootLeftInput = true;
				shootUpInput = true;
				speed /= 1.41421;
				break;
			default:
				break;
			}

		}
		else
		{
			// This is for standard fireball creation - here we get the direction od the fireball
			shootUpInput = Engine::InputManager::IsActionActive(input, "PlayerShootUp");
			shootDownInput = Engine::InputManager::IsActionActive(input, "PlayerShootDown");
			shootLeftInput = Engine::InputManager::IsActionActive(input, "PlayerShootLeft");
			shootRightInput = Engine::InputManager::IsActionActive(input, "PlayerShootRight");
		}

		// Here we apply the correct direction to the fireball and the direction if else is used for the triple shot item
		if (shootUpInput && shootLeftInput) {
			auto move = fireball->GetComponent<Engine::MoverComponent>();
			move->m_TranslationSpeed.y = -speed;
			move->m_TranslationSpeed.x = -speed;
			if (direction == 1)
			{
				move->m_TranslationSpeed.x = -speed*0.8f;
				move->m_TranslationSpeed.y = -speed*1.2f;
			}
			else if (direction == 2)
			{
				move->m_TranslationSpeed.x = -speed*1.2f;
				move->m_TranslationSpeed.y = -speed*0.8f;
			}
		}
		else if (shootUpInput && shootRightInput) {
			auto move = fireball->GetComponent<Engine::MoverComponent>();
			move->m_TranslationSpeed.y = -speed;
			move->m_TranslationSpeed.x = speed;
			if (direction == 1)
			{
				move->m_TranslationSpeed.x = speed * 0.8f;
				move->m_TranslationSpeed.y = -speed * 1.2f;
			}
			else if (direction == 2)
			{
				move->m_TranslationSpeed.x = speed * 1.2f;
				move->m_TranslationSpeed.y = -speed * 0.8f;
			}
		}
		else if (shootDownInput && shootLeftInput) {
			auto move = fireball->GetComponent<Engine::MoverComponent>();
			move->m_TranslationSpeed.y = speed;
			move->m_TranslationSpeed.x = -speed;
			if (direction == 1)
			{
				move->m_TranslationSpeed.x = -speed * 0.8f;
				move->m_TranslationSpeed.y = speed * 1.2f;
			}
			else if (direction == 2)
			{
				move->m_TranslationSpeed.x = -speed * 1.2f;
				move->m_TranslationSpeed.y = speed * 0.8f;
			}
		}
		else if (shootDownInput && shootRightInput) {
			auto move = fireball->GetComponent<Engine::MoverComponent>();
			move->m_TranslationSpeed.y = speed;
			move->m_TranslationSpeed.x = speed;
			if (direction == 1)
			{
				move->m_TranslationSpeed.x = speed * 0.8f;
				move->m_TranslationSpeed.y = speed * 1.2f;
			}
			else if (direction == 2)
			{
				move->m_TranslationSpeed.x = speed * 1.2f;
				move->m_TranslationSpeed.y = speed * 0.8f;
			}
		}
		else {
			if (shootUpInput) {
				auto move = fireball->GetComponent<Engine::MoverComponent>();
				move->m_TranslationSpeed.y = -speed;
				if (direction == 1)
				{
					move->m_TranslationSpeed.x = -speed / 4;
				}
				else if (direction == 2)
				{
					move->m_TranslationSpeed.x = speed / 4;
				}
			}
			else if (shootDownInput) {
				auto move = fireball->GetComponent<Engine::MoverComponent>();
				move->m_TranslationSpeed.y = speed;
				if (direction == 1)
				{
					move->m_TranslationSpeed.x = -speed / 4;
				}
				else if (direction == 2)
				{
					move->m_TranslationSpeed.x = speed / 4;
				}
			}

			if (shootLeftInput) {
				auto move = fireball->GetComponent<Engine::MoverComponent>();
				move->m_TranslationSpeed.x = -speed;
				if (direction == 1)
				{
					move->m_TranslationSpeed.y = -speed / 4;
				}
				else if (direction == 2)
				{
					move->m_TranslationSpeed.y = speed / 4;
				}
			}
			else  if (shootRightInput) {
				auto move = fireball->GetComponent<Engine::MoverComponent>();
				move->m_TranslationSpeed.x = speed;
				if (direction == 1)
				{
					move->m_TranslationSpeed.y = -speed / 4;
				}
				else if (direction == 2)
				{
					move->m_TranslationSpeed.y = speed / 4;
				}
			}
		}

		entityManager_->AddEntity(std::move(fireball));


		return !(entityManager_->GetAllEntitiesWithComponent<Engine::FireballComponent>().empty());
	}

	void UpdateFireballs(Engine::EntityManager* entityManager_, Engine::AudioSystem* audioSystem_) {

		// EntitiesToMove is not just a copy pasta went wrong :D aw who am I kidding... Shame on us
		auto entitiesToMove = entityManager_->GetAllEntitiesWithComponents<Engine::FireballComponent>();

		for (auto& fireball : entitiesToMove)
		{
			// Fireball spinning animation
			auto* sprite = fireball->GetComponent<Engine::SpriteComponent>();

			int ticks = (SDL_GetTicks() / 200) % 4;

			SDL_Rect new_rect{ 50 + (12 * ticks), 0, 11, 11 };
			sprite->m_src = new_rect;

			auto collider = fireball->GetComponent<Engine::CollisionComponent>();

			for (auto* entity : collider->m_CollidedWith)
			{
				// The beautiful patch to our exception problem 
				if (entity->GetId() > 10000000) {
					continue;
				}
				if (entity != nullptr) {
					
					// If we hit an npc with a fireball 
					if (entity->HasComponent<Engine::NPCComponent>())
					{
						
						// Malo sam vam menjao ovo, jer sam dodao HP componentu neprijateljima, u sustini jedan if-else
						// koji provera hp, ukratko, fire i water imace po 2hp-a, wind i mental 1hp i earth 3hp-a
						auto npcHp = entity->GetComponent<Engine::HealthComponent>();
						if (npcHp->m_CurrentHealth > 1)
						{
							if (entity->HasComponent<FireNPCComponent>())audioSystem_->PlaySoundEffect("fireDeath"); 
							audioSystem_->PlaySoundEffect("slam");
							npcHp->m_CurrentHealth--; // Lower the hp of the npc if it has more then 1hp
							entityManager_->RemoveEntity(fireball->GetId()); // Destroy the fireball
						}
						else if (entity->HasComponent<WaterNPCComponent>() && !entity->GetComponent<WaterNPCComponent>()->isInWallForm && npcHp->m_CurrentHealth == 1)
						{
							// When we kill a water elemental it freezes over to make a wall that has 3 hp
							audioSystem_->PlaySoundEffect("freeze");
							entity->GetComponent<WaterNPCComponent>()->isInWallForm = true;
							entity->RemoveComponent<Engine::MoverComponent>();
							entity->AddComponent<Engine::WallComponent>();
							entity->GetComponent<Engine::HealthComponent>()->m_CurrentHealth = 3;
						}
						else
						{
							// Here the elementals release their death cries
							if (entity->HasComponent<WaterNPCComponent>()) 
							{
								audioSystem_->PlaySoundEffect("slam");
								audioSystem_->PlaySoundEffect("waterDeath");
							}
							else if (entity->HasComponent<EarthNPCComponent>()) 
							{
								audioSystem_->PlaySoundEffect("slam");
								audioSystem_->PlaySoundEffect("rockDeath");
							}
							else if (entity->HasComponent<WindNPCComponent>()) 
							{
								audioSystem_->PlaySoundEffect("slam");
								audioSystem_->PlaySoundEffect("airDeath");
							}
							else if (entity->HasComponent<MentalNPCComponent>()) 
							{
								audioSystem_->PlaySoundEffect("slam");
								audioSystem_->PlaySoundEffect("mentalDeath");
							}
							else if (entity->HasComponent<FireNPCComponent>()) 
							{
								if(entity->GetComponent<Engine::TransformComponent>()->m_Size.x<50)
								{
									audioSystem_->PlaySoundEffect("slam");
									audioSystem_->PlaySoundEffect("smallFireDeath");
								}
								else 
								{
									audioSystem_->PlaySoundEffect("slam");
									audioSystem_->PlaySoundEffect("fireDeath");
								}
								
							}
							
							auto itemStash = entityManager_->GetAllEntitiesWithComponents<Engine::ItemStashComponent>()[0];
							auto itemSprite = itemStash->GetComponent<Engine::SpriteComponent>();
							
							// The entity drops a random item upon death
							double r = ((double)std::rand() / (RAND_MAX));
							if(r < 0.2)
								CreateItem(entityManager_, rand()%7, itemSprite->m_Image, entity);
							entityManager_->RemoveEntity(fireball->GetId());
							entityManager_->RemoveEntity(entity->GetId());
						}
						

						break;
					}
				}

				// Remove the fireball if it hits an obstacle or the border
				if (entity->HasComponent<Engine::BorderComponent>() || entity->HasComponent<Engine::ObstacleComponent>())
				{
					
					entityManager_->RemoveEntity(fireball->GetId());
					break;
				}
			}



		}
	}
}