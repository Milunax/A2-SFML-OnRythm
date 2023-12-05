#include "GameManager.h"


GameManager::GameManager() 
{
	_gameState = GameState::START_MENU;
}

GameState GameManager::GetGameState() 
{
	return _gameState;
}

void GameManager::SetGameState(GameState state) 
{
	_gameState = state;
}
