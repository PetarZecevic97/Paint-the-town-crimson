#pragma once

namespace Game
{
	enum class EnemyType
	{
		Invalid,
		Mental,
		Water,
		Earth,
		Wind,
		Fire
	};

	struct EnemyComponent : public Engine::Component
	{
		EnemyType m_Type{ EnemyType::Invalid };
		EnemyComponent(EnemyType enemyType) : m_Type(enemyType) {}
	};

	struct WaterNPCComponent : public Engine::Component
	{
		bool isInWallForm = false;
	};

	struct FireNPCComponent : public Engine::Component
	{
		bool m_isSplited = false;
	};

	struct WindNPCComponent : public Engine::Component
	{

	};

	struct EarthNPCComponent : public Engine::Component
	{

	};

	struct MentalNPCComponent : public Engine::Component
	{

	};
}