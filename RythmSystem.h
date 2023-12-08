#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <array>
#include "RefsData.h"
#include "Player.h"
#include "WaveManager.h"
#include "GameManager.h"

enum class BeatState
{
	NONE,
	NORMAL,
	NORMAL1_2,
	NORMAL1_3,
	NORMAL2,
	SLOW,
	SLOW2,
	SLOW2_2,
	PAUSE,
	BOSS,
	BOSSSUBSTATE
};

BeatState GetStateOfBeat(std::map<int, BeatState> lvl, int beat, BeatState actualState);

class RythmSystem 
{
	public :
		RythmSystem(RefsData data);
		void Init(WaveManager* waveManager, Player* player, GameManager* gameManager);
		void ChangeSong(RefsData data, float& bpm, float& tick, int& tickCount);
		void MainSequence(int tickCount);
		void TweenCreationAndUpdate(float iTime);
		void Draw(RefsData data);

	private :

		sf::Color _backgroundColor;
		std::map<int, BeatState> _level_1;
		std::map<int, BeatState> _level_2;
		std::map<int, BeatState> _level_3;
		std::array<std::map<int, BeatState>, 3> _levelArray;
		std::map<int, BeatState> _actualLVL;
		int _actualLVLCount = 0;
		BeatState _actualState = BeatState::SLOW;

		sf::Shader _backgroundShaderNormal;
		sf::Shader _backgroundShaderNormal2;
		sf::Shader _backgroundShaderSlow;
		sf::Shader _backgroundShaderSlow2;
		sf::Shader _backgroundShaderBoss;
		sf::Shader _backgroundShaderPause;

		sf::Vector3f _NormalA;
		sf::Vector3f _NormalB;
		sf::Vector3f _NormalC;
		sf::Vector3f _NormalD;

		sf::RectangleShape _backgroundRect;
		sf::RenderStates _backgroundStates;

		WaveManager* _waveManager;
		GameManager* _gameManager;
		Player* _player;
};

