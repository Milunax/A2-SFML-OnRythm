#pragma once

enum class GameState
{
	START_MENU,
	IN_GAME,
	UPGRADES
};


class GameManager 
{
	public :
		GameManager();
		GameState GetGameState();
		void SetGameState(GameState state);
	private :
		GameState _gameState;
};
