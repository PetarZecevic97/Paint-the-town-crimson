#pragma once


namespace Game 
{
	enum class LevelNumber
	{
		LEVEL_ONE = 0,
		LEVEL_TWO,
		LEVEL_THREE,
		NUM_OF_LEVELS
	};

	static LevelNumber gLevelNumber = LevelNumber::LEVEL_ONE;
}