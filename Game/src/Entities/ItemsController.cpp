#include "ItemsController.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

namespace Game
{

	bool CreateItem(Engine::EntityManager* entityManager_, int item_type, Engine::Texture* texture, Engine::Entity* npc) {
		ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to ProjectileController::Init()");

		auto item = std::make_unique<Engine::Entity>();
		auto npc_trans = npc->GetComponent<Engine::TransformComponent>();
		float x = npc_trans->m_Position[0];
		float y = npc_trans->m_Position[1];

		item->AddComponent<Engine::TransformComponent>(x, y, 40.f, 40.f);
		item->AddComponent<Engine::CollisionComponent>(40.f, 40.f);
		item->AddComponent<Engine::ItemComponent>(SDL_GetTicks());
		item->GetComponent<Engine::ItemComponent>()->m_itemType = item_type;
		item->AddComponent<Engine::SpriteComponent>().m_Image = texture;

		SDL_Rect new_rect;
		switch (item_type) {
			//lives
		case 0:
			new_rect = { 0, 0, 19, 12 };
			break;
			//speed
		case 1:
			new_rect = { 60, 0, 15, 19 };
			break;
			//rapid fireballs
		case 2:
			new_rect = { 80, 0, 18, 13 };
			break;
			//destroyer of worlds
		case 3:
			new_rect = { 0, 45, 24, 22 };
			break;
			//timelord
		case 4:
			new_rect = { 60, 20, 13, 15 };
			break;
			//triple
		case 5:
			new_rect = { 20, 0, 40, 11 };
			break;
			//360 noscope
		case 6:
			new_rect = { 0, 20, 24, 24 };
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

	void UpdateItems(Engine::EntityManager* entityManager_, Engine::Texture* texture) {

		UpdateExplosion(entityManager_);

		auto items = entityManager_->GetAllEntitiesWithComponents<Engine::ItemComponent>();

		for (auto* item : items)
		{


			if (static_cast<int>(SDL_GetTicks()) > item->GetComponent<Engine::ItemComponent>()->m_timeCreated + 8000) {
				if (item->GetComponent<Engine::TransformComponent>()->m_Position.x == -2000) {
					auto player = entityManager_->GetAllEntitiesWithComponent< Engine::PlayerComponent>()[0];
					player->GetComponent<Engine::PlayerComponent>()->m_apocalypse = false;
					

				}
				entityManager_->RemoveEntity(item->GetId());
				continue;
			}

			auto collider = item->GetComponent<Engine::CollisionComponent>();


			for (auto* entity : collider->m_CollidedWith)
			{
				if (entity->HasComponent<Engine::PlayerComponent>())
				{
					//temporary solution for lives and apocalypse
					//we need the items to last a little bit longer so that we can do an animation
					if (item->GetComponent<Engine::ItemComponent>()->m_itemType == 0 || item->GetComponent<Engine::ItemComponent>()->m_itemType == 3) {

						if (item->GetComponent<Engine::ItemComponent>()->m_itemType == 0)
						{
							auto player = entityManager_->GetAllEntitiesWithComponent< Engine::PlayerComponent>()[0];
							player->GetComponent<Engine::PlayerComponent>()->m_number_of_lives++;
						}
						else
						{
							auto player = entityManager_->GetAllEntitiesWithComponent< Engine::PlayerComponent>()[0];
							player->GetComponent<Engine::PlayerComponent>()->m_apocalypse = true;
							auto enemies = entityManager_->GetAllEntitiesWithComponents<Engine::NPCComponent>();
							for (auto* enemy : enemies) {
								entityManager_->RemoveEntity(enemy->GetId());
							}
							item->GetComponent<Engine::ItemComponent>()->m_timeCreated = SDL_GetTicks();
							item->GetComponent<Engine::TransformComponent>()->m_Position.x = -2000;
							item->GetComponent<Engine::TransformComponent>()->m_Position.y = -2000;

							CreateExplosion(entityManager_, texture);
							

							/* item->RemoveComponent<Engine::CollisionComponent>();
							item->RemoveComponent<Engine::SpriteComponent>();
							item->RemoveComponent<Engine::ItemComponent>();*/
						}
						
					}
					else {

						if (item->GetComponent<Engine::ItemComponent>()->m_itemType == 1 && entity->GetComponent<Engine::PlayerComponent>()->m_speedBuff)
						{
							auto speedBuff = entityManager_->GetAllEntitiesWithComponents<Engine::SpeedBuffComponent>()[0];
							speedBuff->GetComponent<Engine::BuffComponent>()->m_timeExpires += speedBuff->GetComponent<Engine::BuffComponent>()->m_duration;
						}
						else if (item->GetComponent<Engine::ItemComponent>()->m_itemType == 2 && entity->GetComponent<Engine::PlayerComponent>()->m_rapidFire)
						{
							auto rapidBuff = entityManager_->GetAllEntitiesWithComponents<Engine::RapidBuffComponent>()[0];
							rapidBuff->GetComponent<Engine::BuffComponent>()->m_timeExpires += rapidBuff->GetComponent<Engine::BuffComponent>()->m_duration;
						}
						else if (item->GetComponent<Engine::ItemComponent>()->m_itemType == 4 && entity->GetComponent<Engine::PlayerComponent>()->m_timeoutBuff)
						{
							auto timeoutBuff = entityManager_->GetAllEntitiesWithComponents<Engine::TimestopBuffComponent>()[0];
							timeoutBuff->GetComponent<Engine::BuffComponent>()->m_timeExpires += timeoutBuff->GetComponent<Engine::BuffComponent>()->m_duration;
						}
						else if (item->GetComponent<Engine::ItemComponent>()->m_itemType == 5 && entity->GetComponent<Engine::PlayerComponent>()->m_tripleshotBuff)
						{
							auto tripleBuff = entityManager_->GetAllEntitiesWithComponents<Engine::TripleBuffComponent>()[0];
							tripleBuff->GetComponent<Engine::BuffComponent>()->m_timeExpires += tripleBuff->GetComponent<Engine::BuffComponent>()->m_duration;
						}
						else if (item->GetComponent<Engine::ItemComponent>()->m_itemType == 6 && entity->GetComponent<Engine::PlayerComponent>()->m_multishotBuff)
						{
							auto multiBuff = entityManager_->GetAllEntitiesWithComponents<Engine::MultiBuffComponent>()[0];
							multiBuff->GetComponent<Engine::BuffComponent>()->m_timeExpires += multiBuff->GetComponent<Engine::BuffComponent>()->m_duration;
						}
						else
						{
							auto player = entityManager_->GetAllEntitiesWithComponent< Engine::PlayerComponent>()[0];
							auto buff = std::make_unique<Engine::Entity>();
							buff->AddComponent<Engine::BuffComponent>(SDL_GetTicks());
							buff->GetComponent<Engine::BuffComponent>()->m_timeExpires = buff->GetComponent<Engine::BuffComponent>()->m_timeCreated + buff->GetComponent<Engine::BuffComponent>()->m_duration;
							buff->GetComponent<Engine::BuffComponent>()->m_buffType = item->GetComponent<Engine::ItemComponent>()->m_itemType;

							if (item->GetComponent<Engine::ItemComponent>()->m_itemType == 1)
							{
								buff->AddComponent<Engine::SpeedBuffComponent>();
								player->GetComponent<Engine::PlayerComponent>()->m_speedBuff = true;
								player->GetComponent<Engine::PlayerComponent>()->m_speed += 200;
							}
							else if (item->GetComponent<Engine::ItemComponent>()->m_itemType == 2)
							{
								buff->AddComponent<Engine::RapidBuffComponent>();
								player->GetComponent<Engine::PlayerComponent>()->m_rapidFire = true;
								player->GetComponent<Engine::PlayerComponent>()->m_fireballCooldown -= 400;
							}
							else if (item->GetComponent<Engine::ItemComponent>()->m_itemType == 4)
							{
								buff->AddComponent<Engine::TimestopBuffComponent>();
								player->GetComponent<Engine::PlayerComponent>()->m_timeoutBuff = true;
							}
							else if (item->GetComponent<Engine::ItemComponent>()->m_itemType == 5)
							{
								buff->AddComponent<Engine::TripleBuffComponent>();
								player->GetComponent<Engine::PlayerComponent>()->m_tripleshotBuff = true;
							}
							else if (item->GetComponent<Engine::ItemComponent>()->m_itemType == 6)
							{
								buff->AddComponent<Engine::MultiBuffComponent>();
								player->GetComponent<Engine::PlayerComponent>()->m_multishotBuff = true;
							}

							entityManager_->AddEntity(std::move(buff));

						}
						entityManager_->RemoveEntity(item->GetId());



					}
					break;
				}
			}

		}

		auto buffs = entityManager_->GetAllEntitiesWithComponents<Engine::BuffComponent>();
		auto player = entityManager_->GetAllEntitiesWithComponent< Engine::PlayerComponent>()[0];

		for (auto* buff : buffs)
		{
			auto buffComponent = buff->GetComponent<Engine::BuffComponent>();
			if (static_cast<int>(SDL_GetTicks()) > buffComponent->m_timeExpires) {
				if (buffComponent->m_buffType == 1)
				{
					player->GetComponent<Engine::PlayerComponent>()->m_speed -= 200;
					player->GetComponent<Engine::PlayerComponent>()->m_speedBuff = false;
				}
				else if (buffComponent->m_buffType == 2)
				{
					player->GetComponent<Engine::PlayerComponent>()->m_fireballCooldown += 400;
					player->GetComponent<Engine::PlayerComponent>()->m_rapidFire = false;
				}
				else if (buffComponent->m_buffType == 4)
				{
					player->GetComponent<Engine::PlayerComponent>()->m_timeoutBuff = false;
				}
				else if (buffComponent->m_buffType == 5)
				{
					player->GetComponent<Engine::PlayerComponent>()->m_tripleshotBuff = false;
				}
				else if (buffComponent->m_buffType == 6)
				{
					player->GetComponent<Engine::PlayerComponent>()->m_multishotBuff = false;
				}
				entityManager_->RemoveEntity(buff->GetId());
				continue;
			}
		}

	}

	void CreateExplosion(Engine::EntityManager* entityManager_, Engine::Texture* texture) {

		srand(static_cast<int>(time(NULL)));
		int aca = rand() % 100;
		
		for (int i = 0; i < 14; i++) {
			auto explosion = std::make_unique<Engine::Entity>();

			explosion->AddComponent<Engine::TransformComponent>(static_cast<float>(rand() % 7 * 128.f * pow(-1, rand() % 100)  + rand() % 256 * pow(-1, rand() % 100)), static_cast<float>(rand() % 7 * 128.f * pow(-1, rand() % 100) + rand() % 256 * pow(-1, rand() % 100)), static_cast<float>(256), static_cast<float>(256));
			explosion->AddComponent<Engine::SpriteComponent>().m_Image = texture;
			explosion->AddComponent<Engine::ExplosionComponent>();
			explosion->GetComponent<Engine::ExplosionComponent>()->m_last_time_changed = SDL_GetTicks() - 200;

			auto* explosion_sprite = explosion->GetComponent<Engine::SpriteComponent>();
			SDL_Rect new_explosion_rect{ 0, 0, 128, 128 };
			explosion_sprite->m_src = new_explosion_rect;
			explosion_sprite->m_Animation = true;

			entityManager_->AddEntity(std::move(explosion));
		}
	
	}

	void UpdateExplosion(Engine::EntityManager* entityManager_) {

		auto explosions = entityManager_->GetAllEntitiesWithComponent<Engine::ExplosionComponent>();

		for (auto* explosion : explosions) {

			int ticks = SDL_GetTicks();
			if (ticks > explosion->GetComponent<Engine::ExplosionComponent>()->m_last_time_changed + 200) {
				explosion->GetComponent<Engine::ExplosionComponent>()->m_last_time_changed = ticks;
				auto* explosion_sprite = explosion->GetComponent<Engine::SpriteComponent>();
				SDL_Rect new_explosion_rect{ 128 * explosion->GetComponent<Engine::ExplosionComponent>()->m_frame_counter, 0, 128, 128 };
				explosion_sprite->m_src = new_explosion_rect;
				explosion->GetComponent<Engine::ExplosionComponent>()->m_frame_counter++;
			}

			if (explosion->GetComponent<Engine::ExplosionComponent>()->m_frame_counter == 12) {	
					entityManager_->RemoveEntity(explosion->GetId());	
			}
		}
	
	}


}