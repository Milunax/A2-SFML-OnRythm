#include "GameManager.h"


GameManager::GameManager() 
{
	_gameState = GameState::START_MENU;
	_frameClock = nullptr;
	_music = nullptr;
	_upgradeManager = nullptr;
}

void GameManager::Init(RefsData data, UpgradeManager* upgradeManager)
{
	_frameClock = data.frameClock;
	_music = data.music;
	_upgradeManager = upgradeManager;
}

GameState GameManager::GetGameState() 
{
	return _gameState;
}

void GameManager::SetGameState(GameState state) 
{
	_gameState = state;
}

void GameManager::StartGame() 
{
	_gameState = GameState::IN_GAME;
	_frameClock->restart().asSeconds();
	//if (!_music->openFromFile("../sound/150.wav"))
	//	std::cout << "Wrong music file" << std::endl;
	//	return;
	_music->play();
	_music->setLoop(false);
}

void GameManager::PauseGame() 
{
	_music->pause();
}

void GameManager::ResumeGame()
{
	_frameClock->restart().asSeconds();
	_music->play();
	_gameState = GameState::IN_GAME;
}

void GameManager::ToUpgradeState() 
{
	PauseGame();

	_upgradeManager->GenerateNewUpgrades();

	_gameState = GameState::UPGRADES;
}
