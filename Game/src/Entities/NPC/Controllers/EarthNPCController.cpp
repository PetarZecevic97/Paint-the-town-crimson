#include "precomp.h"

#include "EarthNPCController.h"

#include "Entities/NPC/EnemySpecificEntities.h"
#include "..//EnemyAnimation.h"

namespace Game
{
	bool EarthNPCController::Init(Engine::EntityManager* entityManager, Engine::Texture* texture, vec2 spawnPosition)
	{
		ASSERT(entityManager != nullptr, "Must pass valid pointer to entitymanager to EarthNPCCOntroller::Init()");
		ASSERT(texture != nullptr, "Must pass valid pointer to texture to EarthNPCCOntroller::Init()");

		auto enemy = std::make_unique<Engine::Entity>();
		enemy->AddComponent<Engine::NPCComponent>();
		enemy->AddComponent<EnemyComponent>(EnemyType::Earth);
		enemy->AddComponent<EarthNPCComponent>();
		enemy->AddComponent<Engine::TransformComponent>(spawnPosition.x, spawnPosition.y, 78.f, 78.f);
		enemy->AddComponent<Engine::CollisionComponent>(78.f, 78.f);
		enemy->AddComponent<Engine::MoverComponent>();
		enemy->AddComponent<Engine::HealthComponent>(3, 3);
		enemy->AddComponent<Engine::SpriteComponent>().m_Image = texture;
		auto* sprite = enemy->GetComponent<Engine::SpriteComponent>();
		SDL_Rect new_rect{ 0, 0, 50, 50 };
		sprite->m_src = new_rect;
		sprite->m_Animation = true;
		entityManager->AddEntity(std::move(enemy));

		return true;
	}

	void EarthNPCController::Update(float dt, Engine::EntityManager* entityManager)
	{
		auto eearthNPC = entityManager->GetAllEntitiesWithComponent<EarthNPCComponent>();

		for (auto& enemy : eearthNPC)
		{
			auto mover = enemy->GetComponent<Engine::MoverComponent>();
			mover->m_TranslationSpeed.x = mover->m_TranslationSpeed.x * 0.4f;
			mover->m_TranslationSpeed.y = mover->m_TranslationSpeed.y * 0.4f;

			auto coll = enemy->GetComponent<Engine::CollisionComponent>()->m_CollidedWith;
			for (auto& coller : coll)
			{
				if (coller->GetId() > 10000000) {
					continue;
				}
				if (coller->HasComponent<Engine::WallComponent>())
				{
					mover->m_TranslationSpeed.x = mover->m_TranslationSpeed.x * 10.f / 4.f;
					mover->m_TranslationSpeed.y = mover->m_TranslationSpeed.y * 10.f / 4.f;
					break;
				}
			}


			ElementalAnimation(entityManager->GetAllEntitiesWithComponent<Engine::PlayerComponent>()[0], enemy, 3);
		}
	}

	bool EarthNPCController::ShutDown()
	{
		return true;
	}
}
