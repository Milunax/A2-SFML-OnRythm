#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "RefsData.h"
#include "UpgradeManager.h"

enum class GameState
{
	START_MENU,
	IN_GAME,
	UPGRADES,
	END_OF_GAME
};

class GameManager 
{
	public :
		GameManager();
		void Init(RefsData data, UpgradeManager* upgradeManager);
		GameState GetGameState();
		void SetGameState(GameState state);
		void StartGame();
		void PauseGame();
		void ResumeGame();
		void ToUpgradeState();
		void ToEndState();
		void AddScore(int value);
		void Draw(RefsData data);
	private :
		GameState _gameState;
		sf::Clock* _frameClock;
		sf::Music* _music;

		int _score;

		UpgradeManager* _upgradeManager;
};
