#include "EnemyAnimation.h"
#include "Entities/NPC/EnemySpecificEntities.h"


void ElementalAnimation(Engine::Entity* player, Engine::Entity* npc, int elemental_type) {

	auto transform = npc->GetComponent<Engine::TransformComponent>();
	auto pmover = player->GetComponent<Engine::TransformComponent>();
	auto sprite = npc->GetComponent<Engine::SpriteComponent>();

	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;
	int number_of_frames = 4;

	switch (elemental_type) {
	case 0:
		number_of_frames = 3;
		break;
	case 1:
		number_of_frames = 4;
		break;
	case 2:
		number_of_frames = 2;
		break;
	case 3:
		number_of_frames = 2;
		break;
	case 4:
		number_of_frames = 4;
		break;
	default:
		number_of_frames = 2;
		break;
	}




	if (pmover->m_Position.x > transform->m_Position.x + 50) {
		moveRight = true;

	}
	else if (pmover->m_Position.x < transform->m_Position.x - 50) {
		moveLeft = true;

	}

	if (pmover->m_Position.y > transform->m_Position.y) {
		moveDown = true;

	}
	else {
		moveUp = true;

	}

	if (!(moveUp || moveDown || moveLeft || moveRight)) {
		int ticks = (SDL_GetTicks() / 200) % number_of_frames;

		SDL_Rect new_rect{ 50 * ticks, 0, 50, 50 };
		sprite->m_src = new_rect;
	}
	else if (moveRight) {
		int ticks = (SDL_GetTicks() / 200) % number_of_frames;

		SDL_Rect new_rect{ 50 * ticks, 100, 50, 50 };
		sprite->m_src = new_rect;
	}
	else if (moveLeft) {
		int ticks = (SDL_GetTicks() / 200) % number_of_frames;

		SDL_Rect new_rect{ 50 * ticks, 150, 50, 50 };
		sprite->m_src = new_rect;
	}
	else if (moveDown) {
		int ticks = (SDL_GetTicks() / 200) % number_of_frames;

		SDL_Rect new_rect{ 50 * ticks, 0, 50, 50 };
		sprite->m_src = new_rect;
	}
	else if (moveUp) {
		int ticks = (SDL_GetTicks() / 200) % number_of_frames;

		SDL_Rect new_rect{ 50 * ticks, 50, 50, 50 };
		sprite->m_src = new_rect;
	}

	if (elemental_type == 0) {
		if (npc->GetComponent<Game::WaterNPCComponent>()->isInWallForm) {
			SDL_Rect new_rect{ 150, 0, 50, 50 };
			sprite->m_src = new_rect;
		}
	}

}
