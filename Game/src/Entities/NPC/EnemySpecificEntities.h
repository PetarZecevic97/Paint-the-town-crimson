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

	struct WaterNPCComponent : public Engine::Component
	{

	};

	struct FireNPCComponent : public Engine::Component
	{

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