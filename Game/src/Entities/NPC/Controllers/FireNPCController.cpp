#include "precomp.h"

#include "FireNPCController.h"

#include "Entities/NPC/EnemySpecificEntities.h"
#include "..//EnemyAnimation.h"

namespace Game
{
	bool FireNPCController::Init(Engine::EntityManager* entityManager, Engine::Texture* texture, vec2 spawnPosition)
	{
		ASSERT(entityManager != nullptr, "Must pass valid pointer to entitymanager to FireNPCCOntroller::Init()");
		ASSERT(texture != nullptr, "Must pass valid pointer to texture to FireNPCCOntroller::Init()");

		auto enemy = std::make_unique<Engine::Entity>();
		enemy->AddComponent<Engine::NPCComponent>();
		enemy->AddComponent<EnemyComponent>(EnemyType::Fire);
		enemy->AddComponent<FireNPCComponent>();
		enemy->AddComponent<Engine::TransformComponent>(spawnPosition.x, spawnPosition.y, 50.f, 50.f);
		enemy->AddComponent<Engine::CollisionComponent>(50.f, 50.f);
		enemy->AddComponent<Engine::MoverComponent>();
		enemy->AddComponent<Engine::HealthComponent>(2, 2);
		enemy->AddComponent<Engine::SpriteComponent>().m_Image = texture;

		auto* sprite = enemy->GetComponent<Engine::SpriteComponent>();
		SDL_Rect new_rect{ 0, 0, 50, 50 };
		sprite->m_src = new_rect;
		sprite->m_Animation = true;

		entityManager->AddEntity(std::move(enemy));

		return true;
	}

	void FireNPCController::Update(float dt, Engine::EntityManager* entityManager)
	{
		auto efireNPC = entityManager->GetAllEntitiesWithComponent<FireNPCComponent>();

		for (auto& enemy : efireNPC)
		{
			// CPU

			if (enemy->GetComponent<Engine::HealthComponent>()->m_CurrentHealth == 1)
			{
				if (!enemy->GetComponent<FireNPCComponent>()->m_isSplited)
				{
					auto oldNPCPosition = enemy->GetComponent < Engine::TransformComponent>()->m_Position;
					auto oldNPCSize = enemy->GetComponent < Engine::TransformComponent>()->m_Size;
					//making new small fire
					auto smallfire1 = std::make_unique<Engine::Entity>();
					smallfire1->AddComponent<Engine::NPCComponent>();
					smallfire1->AddComponent<EnemyComponent>(EnemyType::Fire);
					smallfire1->AddComponent<FireNPCComponent>();
					smallfire1->GetComponent<FireNPCComponent>()->m_isSplited = true;
					smallfire1->AddComponent<Engine::TransformComponent>(oldNPCPosition.x, oldNPCPosition.y - oldNPCSize.y/2.f, oldNPCSize.x/2.f, oldNPCSize.y / 2.f);
					smallfire1->AddComponent<Engine::CollisionComponent>(oldNPCSize.x / 2.f, oldNPCSize.y / 2.f);
					smallfire1->AddComponent<Engine::MoverComponent>();
					smallfire1->AddComponent<Engine::HealthComponent>(1, 1);
					smallfire1->AddComponent<Engine::SpriteComponent>().m_Image = enemy->GetComponent<Engine::SpriteComponent>()->m_Image;

					auto* sprite = smallfire1->GetComponent<Engine::SpriteComponent>();
					SDL_Rect new_rect{ 0, 0, 50, 50 };
					sprite->m_src = new_rect;
					sprite->m_Animation = true;

					entityManager->AddEntity(std::move(smallfire1));

					//remaking old one to become small fire

					enemy->GetComponent<FireNPCComponent>()->m_isSplited = true;
					auto enemyTransform = enemy->GetComponent<Engine::TransformComponent>();
					enemyTransform->m_Position = { oldNPCPosition.x, oldNPCPosition.y + oldNPCSize.y / 2.f };
					enemyTransform->m_Size = { oldNPCSize.x / 2.f, oldNPCSize.y / 2.f };
					enemy->GetComponent<Engine::CollisionComponent>()->m_Size = { oldNPCSize.x / 2.f, oldNPCSize.y / 2.f };
				}

				auto mover = enemy->GetComponent<Engine::MoverComponent>();
				mover->m_TranslationSpeed.x = mover->m_TranslationSpeed.x * 1.3f;
				mover->m_TranslationSpeed.y = mover->m_TranslationSpeed.y * 1.3f;

			}

			ElementalAnimation(entityManager->GetAllEntitiesWithComponent<Engine::PlayerComponent>()[0], enemy, 1);
		}
	}

	bool FireNPCController::ShutDown()
	{
		return true;
	}
}
