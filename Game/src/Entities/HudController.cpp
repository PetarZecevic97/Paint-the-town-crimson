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
		life_display->AddComponent<Engine::LifeDisplayComponent>();

		auto* sprite = life_display->GetComponent<Engine::SpriteComponent>();
		SDL_Rect new_rect{ 0, 0, 18, 12 };
		sprite->m_src = new_rect;
		sprite->m_Animation = true;

		entityManager_->AddEntity(std::move(life_display));

		auto x = std::make_unique<Engine::Entity>();

		x->AddComponent<Engine::TransformComponent>(-static_cast<float>(0.44f * window_width), -static_cast<float>(0.46f * window_height), static_cast<float>(16), static_cast<float>(19));
		x->AddComponent<Engine::SpriteComponent>().m_Image = texture_manager_->GetTexture("numbers");
		x->AddComponent<Engine::XComponent>();

		auto* x_sprite = x->GetComponent<Engine::SpriteComponent>();
		SDL_Rect new_x_rect{ 1, 12, 13, 13 };
		x_sprite->m_src = new_x_rect;
		x_sprite->m_Animation = true;

		entityManager_->AddEntity(std::move(x));

		auto player = entityManager_->GetAllEntitiesWithComponent< Engine::PlayerComponent>()[0];
		auto number_of_lives = player->GetComponent<Engine::PlayerComponent>()->m_number_of_lives;

		auto number = std::make_unique<Engine::Entity>();

		number->AddComponent<Engine::TransformComponent>(-static_cast<float>(0.43f * window_width), -static_cast<float>(0.47f * window_height), static_cast<float>(30), static_cast<float>(40));
		number->AddComponent<Engine::SpriteComponent>().m_Image = texture_manager_->GetTexture("numbers");
		number->AddComponent<Engine::NumberComponent>();

		auto* number_sprite = number->GetComponent<Engine::SpriteComponent>();
		if (number_of_lives < 10) {
			SDL_Rect new_number_rect{ 20 + 30 * number_of_lives, 0, 30, 25 };
			number_sprite->m_src = new_number_rect;
		}
		else {
			SDL_Rect new_number_rect{ 326 + 47 * (number_of_lives-10), 0, 47, 25 };
			number_sprite->m_src = new_number_rect;
		}
		number_sprite->m_Animation = true;

		entityManager_->AddEntity(std::move(number));

		auto slab = std::make_unique<Engine::Entity>();

		slab->AddComponent<Engine::TransformComponent>(-static_cast<float>(0.45f * window_width), 0.f, static_cast<float>(120), static_cast<float>(0.85f * window_height));
		slab->AddComponent<Engine::SpriteComponent>().m_Image = texture_manager_->GetTexture("slab");
		slab->AddComponent<Engine::SlabComponent>();

		entityManager_->AddEntity(std::move(slab));

		auto speed = std::make_unique<Engine::Entity>();

		speed->AddComponent<Engine::TransformComponent>(-static_cast<float>(0.45f * window_width), -static_cast<float>(0.31f * window_height), static_cast<float>(60), static_cast<float>(76));
		speed->AddComponent<Engine::SpriteComponent>().m_Image = texture_manager_->GetTexture("faded");
		speed->AddComponent<Engine::SpeedHudComponent>();

		auto* speed_sprite = speed->GetComponent<Engine::SpriteComponent>();
		SDL_Rect new_speed_rect{ 60, 0, 15, 19 };
		speed_sprite->m_src = new_speed_rect;
		speed_sprite->m_Animation = true;

		entityManager_->AddEntity(std::move(speed));

		auto rapid = std::make_unique<Engine::Entity>();

		rapid->AddComponent<Engine::TransformComponent>(-static_cast<float>(0.45f * window_width), -static_cast<float>(0.18f * window_height), static_cast<float>(72), static_cast<float>(52));
		rapid->AddComponent<Engine::SpriteComponent>().m_Image = texture_manager_->GetTexture("faded");
		rapid->AddComponent<Engine::RapidHudComponent>();

		auto* rapid_sprite = rapid->GetComponent<Engine::SpriteComponent>();
		SDL_Rect new_rapid_rect{ 80, 0, 18, 13 };
		rapid_sprite->m_src = new_rapid_rect;
		rapid_sprite->m_Animation = true;

		entityManager_->AddEntity(std::move(rapid));

		auto destroyer = std::make_unique<Engine::Entity>();

		destroyer->AddComponent<Engine::TransformComponent>(-static_cast<float>(0.45f * window_width), -static_cast<float>(0.06f * window_height), static_cast<float>(60), static_cast<float>(76));
		destroyer->AddComponent<Engine::SpriteComponent>().m_Image = texture_manager_->GetTexture("faded");
		destroyer->AddComponent<Engine::DestroyerHudComponent>();

		auto* destroyer_sprite = destroyer->GetComponent<Engine::SpriteComponent>();
		SDL_Rect new_destroyer_rect{ 60, 0, 15, 19 };
		destroyer_sprite->m_src = new_destroyer_rect;
		destroyer_sprite->m_Animation = true;

		entityManager_->AddEntity(std::move(destroyer));


		auto timelord = std::make_unique<Engine::Entity>();

		timelord->AddComponent<Engine::TransformComponent>(-static_cast<float>(0.45f * window_width), static_cast<float>(0.05f * window_height), static_cast<float>(52), static_cast<float>(60));
		timelord->AddComponent<Engine::SpriteComponent>().m_Image = texture_manager_->GetTexture("faded");
		timelord->AddComponent<Engine::TimelordHudComponent>();

		auto* timelord_sprite = timelord->GetComponent<Engine::SpriteComponent>();
		SDL_Rect new_timelord_rect{ 60, 20, 13, 15 };
		timelord_sprite->m_src = new_timelord_rect;
		timelord_sprite->m_Animation = true;

		entityManager_->AddEntity(std::move(timelord));

		auto triple = std::make_unique<Engine::Entity>();

		triple->AddComponent<Engine::TransformComponent>(-static_cast<float>(0.45f * window_width), static_cast<float>(0.16f * window_height), static_cast<float>(80), static_cast<float>(44));
		triple->AddComponent<Engine::SpriteComponent>().m_Image = texture_manager_->GetTexture("faded");
		triple->AddComponent<Engine::TripleHudComponent>();

		auto* triple_sprite = triple->GetComponent<Engine::SpriteComponent>();
		SDL_Rect new_triple_rect{ 20, 0, 40, 11 };
		triple_sprite->m_src = new_triple_rect;
		triple_sprite->m_Animation = true;

		entityManager_->AddEntity(std::move(triple));

		auto multi = std::make_unique<Engine::Entity>();

		multi->AddComponent<Engine::TransformComponent>(-static_cast<float>(0.45f * window_width), static_cast<float>(0.27f * window_height), static_cast<float>(72), static_cast<float>(72));
		multi->AddComponent<Engine::SpriteComponent>().m_Image = texture_manager_->GetTexture("faded");
		multi->AddComponent<Engine::MultiHudComponent>();

		auto* multi_sprite = multi->GetComponent<Engine::SpriteComponent>();
		SDL_Rect new_multi_rect{ 0, 20, 24, 24 };
		multi_sprite->m_src = new_multi_rect;
		multi_sprite->m_Animation = true;

		entityManager_->AddEntity(std::move(multi));




		return !(entityManager_->GetAllEntitiesWithComponent<Engine::HudComponent>().empty());

		
	}

	void HudController::Update(Engine::EntityManager* entityManager_, Engine::TextureManager* texture_manager_, int window_width, int window_height, bool onResize) {
		
		if (onResize) {
			auto Hud_layer = entityManager_->GetAllEntitiesWithComponents<Engine::HudComponent>()[0];
			auto HudTransform = Hud_layer->GetComponent<Engine::TransformComponent>();

			HudTransform->m_Position.x = -static_cast<float>(0.5f * window_width);
			HudTransform->m_Size.x = static_cast<float>(0.2f * window_width);
			HudTransform->m_Size.y = static_cast<float>(window_height);
		}

		auto player = entityManager_->GetAllEntitiesWithComponent< Engine::PlayerComponent>()[0];
		auto number_of_lives = player->GetComponent<Engine::PlayerComponent>()->m_number_of_lives;

		auto number = entityManager_->GetAllEntitiesWithComponent< Engine::NumberComponent>()[0];
				
		if (number_of_lives != number->GetComponent<Engine::NumberComponent>()->m_last_number) {
			number->GetComponent<Engine::NumberComponent>()->m_last_number = number_of_lives;
			auto* number_sprite = number->GetComponent<Engine::SpriteComponent>();
			if (number_of_lives < 10) {
				SDL_Rect new_number_rect{ 20 + 30 * number_of_lives, 0, 30, 25 };
				number_sprite->m_src = new_number_rect;
			}
			else {
				SDL_Rect new_number_rect{ 326 + 46 * (number_of_lives - 10), 0, 46, 25 };
				number_sprite->m_src = new_number_rect;
			}
		}

		if (player->GetComponent<Engine::PlayerComponent>()->m_speed > 200.f) {
			entityManager_->GetAllEntitiesWithComponent< Engine::SpeedHudComponent>()[0]->GetComponent<Engine::SpriteComponent>()->m_Image = texture_manager_->GetTexture("items");
		}else{
			entityManager_->GetAllEntitiesWithComponent< Engine::SpeedHudComponent>()[0]->GetComponent<Engine::SpriteComponent>()->m_Image = texture_manager_->GetTexture("faded");
		}
		//Rapid doesn'work
		if (player->GetComponent<Engine::PlayerComponent>()->m_fireballCooldown < 500.f) {
			entityManager_->GetAllEntitiesWithComponent< Engine::RapidHudComponent>()[0]->GetComponent<Engine::SpriteComponent>()->m_Image = texture_manager_->GetTexture("items");
		}
		else {
			entityManager_->GetAllEntitiesWithComponent< Engine::RapidHudComponent>()[0]->GetComponent<Engine::SpriteComponent>()->m_Image = texture_manager_->GetTexture("faded");
		}

		if (player->GetComponent<Engine::PlayerComponent>()->m_timeoutBuff) {
			entityManager_->GetAllEntitiesWithComponent< Engine::DestroyerHudComponent>()[0]->GetComponent<Engine::SpriteComponent>()->m_Image = texture_manager_->GetTexture("items");
		}
		else {
			entityManager_->GetAllEntitiesWithComponent< Engine::DestroyerHudComponent>()[0]->GetComponent<Engine::SpriteComponent>()->m_Image = texture_manager_->GetTexture("faded");
		}

		if (player->GetComponent<Engine::PlayerComponent>()->m_timeoutBuff) {
			entityManager_->GetAllEntitiesWithComponent< Engine::TimelordHudComponent>()[0]->GetComponent<Engine::SpriteComponent>()->m_Image = texture_manager_->GetTexture("items");
		}
		else {
			entityManager_->GetAllEntitiesWithComponent< Engine::TimelordHudComponent>()[0]->GetComponent<Engine::SpriteComponent>()->m_Image = texture_manager_->GetTexture("faded");
		}

		if (player->GetComponent<Engine::PlayerComponent>()->m_tripleshotBuff) {
			entityManager_->GetAllEntitiesWithComponent< Engine::TripleHudComponent>()[0]->GetComponent<Engine::SpriteComponent>()->m_Image = texture_manager_->GetTexture("items");
		}
		else {
			entityManager_->GetAllEntitiesWithComponent< Engine::TripleHudComponent>()[0]->GetComponent<Engine::SpriteComponent>()->m_Image = texture_manager_->GetTexture("faded");
		}

		if (player->GetComponent<Engine::PlayerComponent>()->m_multishotBuff) {
			entityManager_->GetAllEntitiesWithComponent< Engine::MultiHudComponent>()[0]->GetComponent<Engine::SpriteComponent>()->m_Image = texture_manager_->GetTexture("items");
		}
		else {
			entityManager_->GetAllEntitiesWithComponent< Engine::MultiHudComponent>()[0]->GetComponent<Engine::SpriteComponent>()->m_Image = texture_manager_->GetTexture("faded");
		}

		if (onResize) {
			auto num_transform = number->GetComponent<Engine::TransformComponent>();

			num_transform->m_Position.x = -static_cast<float>(0.43f * window_width);
			num_transform->m_Position.y = -static_cast<float>(0.47f * window_height);

			auto life_display = entityManager_->GetAllEntitiesWithComponent< Engine::LifeDisplayComponent>()[0];

			auto life_display_transform = life_display->GetComponent<Engine::TransformComponent>();
			
			life_display_transform->m_Position.x = -static_cast<float>(0.47f * window_width);
			life_display_transform->m_Position.y = -static_cast<float>(0.47f * window_height);

			auto x = entityManager_->GetAllEntitiesWithComponent< Engine::XComponent>()[0];

			auto x_transform = x->GetComponent<Engine::TransformComponent>();

			x_transform->m_Position.x = -static_cast<float>(0.44f * window_width);
			x_transform->m_Position.y = -static_cast<float>(0.46f * window_height);

			auto slab = entityManager_->GetAllEntitiesWithComponent< Engine::SlabComponent>()[0];

			auto slab_transform = slab->GetComponent<Engine::TransformComponent>();

			slab_transform->m_Position.x = -static_cast<float>(0.45f * window_width);
			slab_transform->m_Size.y = static_cast<float>(0.85f * window_height);

			auto r_speed = entityManager_->GetAllEntitiesWithComponent< Engine::SpeedHudComponent>()[0];

			auto r_speed_transform = r_speed->GetComponent<Engine::TransformComponent>();

			r_speed_transform->m_Position.x = -static_cast<float>(0.45f * window_width);
			r_speed_transform->m_Position.y = -static_cast<float>(0.31f * window_height);

			auto r_rapid = entityManager_->GetAllEntitiesWithComponent< Engine::RapidHudComponent>()[0];

			auto r_rapid_transform = r_rapid->GetComponent<Engine::TransformComponent>();

			r_rapid_transform->m_Position.x = -static_cast<float>(0.45f * window_width);
			r_rapid_transform->m_Position.y = -static_cast<float>(0.18f * window_height);

			auto r_destroyer = entityManager_->GetAllEntitiesWithComponent< Engine::DestroyerHudComponent>()[0];

			auto r_destroyer_transform = r_destroyer->GetComponent<Engine::TransformComponent>();

			r_destroyer_transform->m_Position.x = -static_cast<float>(0.45f * window_width);
			r_destroyer_transform->m_Position.y = -static_cast<float>(0.06f * window_height);

			auto r_timelord = entityManager_->GetAllEntitiesWithComponent< Engine::TimelordHudComponent>()[0];

			auto r_timelord_transform = r_timelord->GetComponent<Engine::TransformComponent>();

			r_timelord_transform->m_Position.x = -static_cast<float>(0.45f * window_width);
			r_timelord_transform->m_Position.y = static_cast<float>(0.05f * window_height);

			auto r_triple = entityManager_->GetAllEntitiesWithComponent< Engine::TripleHudComponent>()[0];

			auto r_triple_transform = r_triple->GetComponent<Engine::TransformComponent>();

			r_triple_transform->m_Position.x = -static_cast<float>(0.45f * window_width);
			r_triple_transform->m_Position.y = static_cast<float>(0.16f * window_height);


			auto r_multi = entityManager_->GetAllEntitiesWithComponent< Engine::MultiHudComponent>()[0];

			auto r_multi_transform = r_multi->GetComponent<Engine::TransformComponent>();

			r_multi_transform->m_Position.x = -static_cast<float>(0.45f * window_width);
			r_multi_transform->m_Position.y = static_cast<float>(0.27f * window_height);

		}


		

	}

}
