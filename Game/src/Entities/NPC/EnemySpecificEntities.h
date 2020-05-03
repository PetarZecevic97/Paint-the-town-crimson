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

	enum class EnemySize
	{
		Invalid,
		Small,
		Medium,
		Large
	};

	struct EnemyComponent : public Engine::Component
	{
		EnemyType m_Type;
		EnemyComponent() : m_Type(EnemyType::Invalid) {}
		EnemyComponent(EnemyType enemyType) : m_Type(enemyType) {}
	};

	struct WaterNPCComponenet : public Engine::Component
	{

	};
}