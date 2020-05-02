#include "precomp.h"

#include "DummyController.h"

#include "Entities/Dummy/DummySpecificEntities.h"



namespace Game
{
	bool DummyController::Init(Engine::EntityManager* entityManager, Engine::Texture* texture)
	{
		ASSERT(entityManager != nullptr, "Must pass valid pointer to entitymanager to DummyController::Init()");
		ASSERT(texture != nullptr, "Must pass valid pointer to texture to DummyController::Init()");

		auto dummy = std::make_unique<Engine::Entity>();

		dummy->AddComponent<DummyComponent>();
		dummy->AddComponent<Engine::TransformComponent>(100.f, 100.f, 50.f, 50.f);
		dummy->AddComponent<Engine::CollisionComponent>(50.f, 50.f);
		dummy->AddComponent<Engine::WallComponent>();
		dummy->AddComponent<Engine::SpriteComponent>().m_Image = texture;

		entityManager->AddEntity(std::move(dummy));
		return true;
	}

	bool DummyController::Init(Engine::EntityManager* entityManager, Engine::Texture* texture, float x, float y)
	{
		ASSERT(entityManager != nullptr, "Must pass valid pointer to entitymanager to DummyController::Init()");
		ASSERT(texture != nullptr, "Must pass valid pointer to texture to DummyController::Init()");

		auto dummy = std::make_unique<Engine::Entity>();

		dummy->AddComponent<DummyComponent>();
		dummy->AddComponent<Engine::TransformComponent>(x, y, 50.f, 50.f);
		dummy->AddComponent<Engine::CollisionComponent>(50.f, 50.f);
		dummy->AddComponent<Engine::WallComponent>();
		dummy->AddComponent<Engine::SpriteComponent>().m_Image = texture;

		entityManager->AddEntity(std::move(dummy));
		return true;
	}

	void DummyController::Update(float dt, Engine::EntityManager* entityManager)
	{
		auto dummies = entityManager->GetAllEntitiesWithComponents<DummyComponent>();
		for (auto& dummy : dummies)
		{
			//Do something if needed
		}
	}
}