#pragma once

namespace Game
{
	enum class EnemyType
	{
		Invalid,
		Water,
		Earth,
		Wind,
		Fire
	};

	struct EnemyComponent : public Engine::Component
	{
		EnemyType m_Type;
		EnemyComponent() : m_Type(EnemyType::Invalid) {}
		EnemyComponent(EnemyType enemyType) : m_Type(enemyType) {}
	};
}