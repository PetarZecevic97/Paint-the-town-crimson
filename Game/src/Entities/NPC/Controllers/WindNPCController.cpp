#include "precomp.h"

#include "WindNPCController.h"

#include "Entities/NPC/EnemySpecificEntities.h"
#include "..//EnemyAnimation.h"

namespace Game
{
	bool WindNPCController::Init(Engine::EntityManager* entityManager, Engine::Texture* texture, vec2 spawnPosition)
	{
		ASSERT(entityManager != nullptr, "Must pass valid pointer to entitymanager to WindNPCCOntroller::Init()");
		ASSERT(texture != nullptr, "Must pass valid pointer to texture to WindNPCCOntroller::Init()");

		auto enemy = std::make_unique<Engine::Entity>();
		enemy->AddComponent<Engine::NPCComponent>();
		enemy->AddComponent<EnemyComponent>(EnemyType::Wind);
		enemy->AddComponent<WindNPCComponent>();
		enemy->AddComponent<Engine::TransformComponent>(spawnPosition.x, spawnPosition.y, 64.f, 64.f);
		enemy->AddComponent<Engine::CollisionComponent>(64.f, 64.f);
		enemy->AddComponent<Engine::MoverComponent>();
		enemy->AddComponent<Engine::HealthComponent>(1, 1);
		enemy->AddComponent<Engine::SpriteComponent>().m_Image = texture;
		auto* sprite = enemy->GetComponent<Engine::SpriteComponent>();
		SDL_Rect new_rect{ 0, 0, 50, 50 };
		sprite->m_src = new_rect;
		sprite->m_Animation = true;
		entityManager->AddEntity(std::move(enemy));

		return true;
	}

	void WindNPCController::Update(float dt, Engine::EntityManager* entityManager)
	{
		auto ewindNPC = entityManager->GetAllEntitiesWithComponent<WindNPCComponent>();

		for (auto& enemy : ewindNPC)
		{
			auto mover = enemy->GetComponent<Engine::MoverComponent>();
			mover->m_TranslationSpeed.x = mover->m_TranslationSpeed.x * 2.3f;
			mover->m_TranslationSpeed.y = mover->m_TranslationSpeed.y * 2.3f;
			ElementalAnimation(entityManager->GetAllEntitiesWithComponent<Engine::PlayerComponent>()[0], enemy, 2);
		}
	}

	bool WindNPCController::ShutDown()
	{
		return true;
	}
}
