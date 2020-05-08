#include "FireballController.h"
#include "ItemsController.h"

namespace Game
{
	bool CreateFireball(Engine::EntityManager* entityManager_, int direction, int direction2) {
		ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to ProjectileController::Init()");

		auto player = entityManager_->GetAllEntitiesWithComponent< Engine::PlayerComponent>()[0];

		auto fireball = std::make_unique<Engine::Entity>();
		auto player_trans = player->GetComponent<Engine::TransformComponent>();
		float x = player_trans->m_Position[0];
		float y = player_trans->m_Position[1];
		auto input = player->GetComponent<Engine::InputComponent>();


		bool moveUpInput = Engine::InputManager::IsActionActive(input, "PlayerMoveUp");
		bool moveDownInput = Engine::InputManager::IsActionActive(input, "PlayerMoveDown");
		bool moveLeftInput = Engine::InputManager::IsActionActive(input, "PlayerMoveLeft");
		bool moveRightInput = Engine::InputManager::IsActionActive(input, "PlayerMoveRight");


		fireball->AddComponent<Engine::TransformComponent>(x - 36 * (((moveUpInput || moveLeftInput) && !moveRightInput && !moveDownInput) ? -1 : 1), y - 6, 22.f, 22.f);
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

		float speed = 300.f;

		bool shootUpInput = false;
		bool shootDownInput = false;
		bool shootLeftInput = false;
		bool shootRightInput = false;
		if (player->GetComponent<Engine::PlayerComponent>()->m_multishotBuff)
		{
			switch (direction2) {
			case 1:
				shootUpInput = true;
				break;
			case 2:
				shootUpInput = true;
				shootRightInput = true;
				speed /= 1.41421;
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
			shootUpInput = Engine::InputManager::IsActionActive(input, "PlayerShootUp");
			shootDownInput = Engine::InputManager::IsActionActive(input, "PlayerShootDown");
			shootLeftInput = Engine::InputManager::IsActionActive(input, "PlayerShootLeft");
			shootRightInput = Engine::InputManager::IsActionActive(input, "PlayerShootRight");
		}

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
					auto itemStash = entityManager_->GetAllEntitiesWithComponents<Engine::ItemStashComponent>()[0];
					auto itemSprite = itemStash->GetComponent<Engine::SpriteComponent>();
					CreateItem(entityManager_, 5, itemSprite->m_Image, entity);
					CreateItem(entityManager_, 6, itemSprite->m_Image, entity);
					CreateItem(entityManager_, 2, itemSprite->m_Image, entity);
					entityManager_->RemoveEntity(fireball->GetId());
					entityManager_->RemoveEntity(entity->GetId());

					break;

				}

				if (entity->HasComponent<Engine::BorderComponent>() || entity->HasComponent<Engine::ObstacleComponent>())
				{
					entityManager_->RemoveEntity(fireball->GetId());
					break;
				}
			}



		}

	}
}