#pragma once


namespace Game 
{
	enum class LevelNumber
	{
		LEVEL_MENU = 0,
		LEVEL_ONE,
		LEVEL_TWO,
		LEVEL_THREE,
		LEVEL_WIN,
		LEVEL_GAME_OVER,
		NUM_OF_LEVELS
	};

	static LevelNumber gLevelNumber = LevelNumber::LEVEL_MENU;
}