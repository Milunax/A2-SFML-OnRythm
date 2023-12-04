#pragma once

enum class GameState
{
	START_MENU,
	IN_GAME,
	PAUSE
};

class GameManager 
{
	public :
		GameManager();
		GameState GetGameState();
	private :
		GameState _gameState;
};
