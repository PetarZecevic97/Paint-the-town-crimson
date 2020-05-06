#include "precomp.h"
#include "HudController.h"

namespace Game
{

	bool HudController::Init(Engine::EntityManager* entityManager_, Engine::TextureManager* texture_manager_, int window_width, int window_height) {
		ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entity manager to HudController::Init()");
		ASSERT(texture_manager_ != nullptr, "Must pass valid pointer to texture manager to HudController::Init()");


		auto hud_layer = std::make_unique<Engine::Entity>();

		hud_layer->AddComponent<Engine::TransformComponent>(-static_cast<float>(0.5f*window_width), 0.f, static_cast<float>(0.2f*window_width), static_cast<float>(window_height));
		hud_layer->AddComponent<Engine::SpriteComponent>().m_Image = texture_manager_->GetTexture("unblank");
		hud_layer->AddComponent<Engine::HudComponent>();
		entityManager_->AddEntity(std::move(hud_layer));

		auto life_display = std::make_unique<Engine::Entity>();

		life_display->AddComponent<Engine::TransformComponent>(-static_cast<float>(0.47f * window_width), -static_cast<float>(0.47f * window_height), static_cast<float>(54), static_cast<float>(36));
		life_display->AddComponent<Engine::SpriteComponent>().m_Image = texture_manager_->GetTexture("items");

		auto* sprite = life_display->GetComponent<Engine::SpriteComponent>();
		SDL_Rect new_rect{ 0, 0, 18, 12 };
		sprite->m_src = new_rect;
		sprite->m_Animation = true;

		entityManager_->AddEntity(std::move(life_display));

		return !(entityManager_->GetAllEntitiesWithComponent<Engine::HudComponent>().empty());

		
	}

	void HudController::Update(Engine::EntityManager* entityManager_, int window_width, int window_height) {
		
		auto Hud_layer = entityManager_->GetAllEntitiesWithComponents<Engine::HudComponent>()[0];
		auto HudTransform = Hud_layer->GetComponent<Engine::TransformComponent>();

		HudTransform->m_Position.x = -static_cast<float>(0.5f * window_width);
		HudTransform->m_Size.x = static_cast<float>(0.2f * window_width);		
		HudTransform->m_Size.y = static_cast<float>(window_height);
		

	}

}
