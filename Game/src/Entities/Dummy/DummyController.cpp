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
		dummy->AddComponent<Engine::TransformComponent>(300.f, 300.f, 30.f, 30.f);
		dummy->AddComponent<Engine::CollisionComponent>(30.f, 30.f);
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