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

void GameManager::AddScore(int value)
{
	_score += value;
}

void GameManager::Draw(RefsData data)
{
	sf::Text scoreText;

	switch (_gameState)
	{
	case GameState::START_MENU:
		break;
	case GameState::IN_GAME:
		scoreText = CreateTextAlone((*data.window), sf::Vector2f(50.0f, 20.0f), *data.baseFont, IntStringConcatenate(_score, "Score : "), 24, sf::Text::Regular);
		data.window->draw(scoreText);
		break;
	case GameState::UPGRADES:
		scoreText = CreateTextAlone((*data.window), sf::Vector2f(50.0f, 20.0f), *data.baseFont, IntStringConcatenate(_score, "Score : "), 24, sf::Text::Regular);
		data.window->draw(scoreText);
		break;
	default:
		break;
	}
}
