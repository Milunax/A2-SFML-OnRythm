#include "RythmSystem.h"
BeatState GetStateOfBeat(std::map<int, BeatState> lvl, int beat, BeatState actualState) {
	for (auto element : lvl) {
		if (element.first == beat) {
			return element.second;
		}
	}
	return actualState;
}


RythmSystem::RythmSystem(RefsData data) 
{
	_level_1 = {
		{32, BeatState::NORMAL},
		{64, BeatState::NORMAL1_2},
		{128, BeatState::NORMAL1_3},
		{192,BeatState::PAUSE} ,
		{223,BeatState::SLOW},
		{288, BeatState::BOSS},
		{289, BeatState::BOSSSUBSTATE} ,
		{320, BeatState::BOSS},
		{321, BeatState::BOSSSUBSTATE} ,
		{352, BeatState::NORMAL},
		{384, BeatState::NORMAL1_2},
		{416,BeatState::PAUSE}
	};
	_level_2 = {
		{0, BeatState::NORMAL2},
		{64, BeatState::NORMAL},
		{124,BeatState::PAUSE} ,
		{128, BeatState::BOSS} ,
		{129, BeatState::BOSSSUBSTATE} ,
		{224,BeatState::SLOW2},
		{228,BeatState::SLOW2_2},
		{232,BeatState::SLOW2},
		{236,BeatState::SLOW2_2},
		{240,BeatState::SLOW2},
		{244,BeatState::SLOW2_2},
		{248,BeatState::SLOW2},
		{252,BeatState::SLOW2_2},
		{256,BeatState::SLOW2},
		{260,BeatState::SLOW2_2},
		{264,BeatState::SLOW2},
		{268,BeatState::SLOW2_2},
		{272,BeatState::SLOW2},
		{276,BeatState::SLOW2_2},
		{280,BeatState::SLOW2},
		{284,BeatState::SLOW2_2},
		{288, BeatState::SLOW} ,
		{320, BeatState::NORMAL} ,
		{324, BeatState::NORMAL1_2} ,
		{328, BeatState::NORMAL} ,
		{332, BeatState::NORMAL1_2} ,
		{336, BeatState::NORMAL} ,
		{340, BeatState::NORMAL1_2} ,
		{344, BeatState::NORMAL} ,
		{348, BeatState::NORMAL1_2} ,
		{352, BeatState::NORMAL} ,
		{356, BeatState::NORMAL1_2} ,
		{360, BeatState::NORMAL} ,
		{364, BeatState::NORMAL1_2} ,
		{368, BeatState::NORMAL} ,
		{372, BeatState::NORMAL1_2} ,
		{376, BeatState::NORMAL} ,
		{380, BeatState::NORMAL1_2} ,
		{384, BeatState::SLOW} , 
		{416, BeatState::NORMAL2},
		{504, BeatState::BOSS} ,
		{505, BeatState::BOSSSUBSTATE} ,
		{536, BeatState::BOSS} ,
		{537, BeatState::BOSSSUBSTATE} ,
		{600, BeatState::NORMAL1_2},
		{632, BeatState::NORMAL1_3},
		{664, BeatState::NORMAL},
		{728,BeatState::SLOW},
		{760,BeatState::SLOW2},
		{764,BeatState::SLOW2_2},
		{768,BeatState::SLOW2},
		{772,BeatState::SLOW2_2},
		{776,BeatState::SLOW2},
		{780,BeatState::SLOW2_2},
		{784,BeatState::SLOW2},
		{788,BeatState::SLOW2_2},
		{792,BeatState::SLOW},
		{856,BeatState::NORMAL2},
		{920,BeatState::PAUSE}
	};
	_level_3 = { {32, BeatState::NORMAL}, {192,BeatState::PAUSE} , {223,BeatState::SLOW}, {288, BeatState::BOSS} };
	_levelArray = { _level_1, _level_2, _level_3 };
	_actualLVL = _level_1;
	_actualLVLCount = 0;
	_actualState = BeatState::SLOW;


	_backgroundShaderNormal.loadFromFile("Background.vert", "Background.frag");
	_backgroundShaderNormal2.loadFromFile("Background.vert", "Background7.frag");
	_backgroundShaderSlow.loadFromFile("Background2.vert", "Background2.frag");
	_backgroundShaderSlow2.loadFromFile("Background2.vert", "Background6.frag");
	_backgroundShaderBoss.loadFromFile("Background.vert", "Background3.frag");
	_backgroundShaderPause.loadFromFile("Background.vert", "Background4.frag");

	_backgroundShaderNormal.setUniform("iResolution", sf::Vector2f((*data.window).getSize()));
	_backgroundShaderNormal2.setUniform("iResolution", sf::Vector2f((*data.window).getSize()));
	_backgroundShaderSlow.setUniform("iResolution", sf::Vector2f((*data.window).getSize()));
	_backgroundShaderSlow2.setUniform("iResolution", sf::Vector2f((*data.window).getSize()));
	_backgroundShaderBoss.setUniform("iResolution", sf::Vector2f((*data.window).getSize()));
	_backgroundShaderPause.setUniform("iResolution", sf::Vector2f((*data.window).getSize()));

	_NormalA = { 0.172f, 0.215f, 0.947f };
	_NormalB = { 0.385f,0.967f,0.336f };
	_NormalC = { 0.813f,0.299f,0.804f };
	_NormalD = { 1.869f,5.081f,2.817f };
	_backgroundShaderNormal.setUniform("a", _NormalA);
	_backgroundShaderNormal.setUniform("b", _NormalB);
	_backgroundShaderNormal.setUniform("c", _NormalC);
	_backgroundShaderNormal.setUniform("d", _NormalD);

	_backgroundShaderSlow2.setUniform("cv", 0.5f);


	_backgroundRect.setPosition(0, 0);
	_backgroundRect.setSize(sf::Vector2f((*data.window).getSize()));

	_waveManager = nullptr;
	_gameManager = nullptr;
	_player = nullptr;
}

void RythmSystem::Init(WaveManager* waveManager, Player* player, GameManager* gameManager)
{
	_waveManager = waveManager;
	_player = player;
	_gameManager = gameManager;
	
	_backgroundStates.shader = &_backgroundShaderSlow;
}

void RythmSystem::ChangeSong(RefsData data, float& bpm, float& tick, int& tickCount)
{
	if ((*data.music).getStatus() == 0) {
		_actualLVLCount++;
		_actualLVL = _levelArray[_actualLVLCount];
		tickCount = 0;
		switch (_actualLVLCount)
		{
		case 1:
			bpm = 145.0;
			tick = 1 / (bpm / 60);
			if (!(*data.music).openFromFile("../sound/145.wav"))
				return; // error
			(*data.music).play();
			break;
		case 2:
			_gameManager->ToEndState();
			break;
		default:
			break;
		}
	}
}

void RythmSystem::MainSequence(int tickCount) 
{

	_actualState = GetStateOfBeat(_actualLVL, tickCount, _actualState);
	std::cout <<"count :" << tickCount << std::endl;

	switch (_actualState)
	{
	case BeatState::NONE:
		std::cout << "lol" << std::endl;
		break;
		//CASE NORMAL : ON BEAT
	case BeatState::NORMAL:
		_NormalA = { 0.172f, 0.215f, 0.947f };
		_NormalB = { 0.385f,0.967f,0.336f };
		_NormalC = { 0.813f,0.299f,0.804f };
		_NormalD = { 1.869f,5.081f,2.817f };
		_backgroundShaderNormal.setUniform("a", _NormalA);
		_backgroundShaderNormal.setUniform("b", _NormalB);
		_backgroundShaderNormal.setUniform("c", _NormalC);
		_backgroundShaderNormal.setUniform("d", _NormalD);
		_backgroundStates.shader = &_backgroundShaderNormal;
		(tickCount % 2 == 0) ? _player->SetColor(sf::Color::Blue) : _player->SetColor(sf::Color::Magenta);
		_waveManager->SetMoveMultiplier(2.0f);
		_waveManager->SetEnemiesNextPosition();
		break;
	case BeatState::NORMAL1_2:
		_NormalA = { 0.650f,0.500f, 0.310f };
		_NormalB = { -0.650f, 0.500f, 0.600f };
		_NormalC = { 0.333f, 0.278f, 0.278f };
		_NormalD = { 0.660f, 0.000f, 0.667f };
		_backgroundShaderNormal.setUniform("a", _NormalA);
		_backgroundShaderNormal.setUniform("b", _NormalB);
		_backgroundShaderNormal.setUniform("c", _NormalC);
		_backgroundShaderNormal.setUniform("d", _NormalD);
		_backgroundStates.shader = &_backgroundShaderNormal;
		(tickCount % 2 == 0) ? _player->SetColor(sf::Color::Blue) : _player->SetColor(sf::Color::Magenta);
		_waveManager->SetMoveMultiplier(2.0f);
		_waveManager->SetEnemiesNextPosition();
		break;
	case BeatState::NORMAL1_3:
		_NormalA = { 0.072f, 0.627f, 0.463f };
		_NormalB = { 0.816f, 0.756f, 0.169f };
		_NormalC = { 0.055f, 0.545f, 0.522f};
		_NormalD = { 3.990f, 4.046f, 0.376f };
		_backgroundShaderNormal.setUniform("a", _NormalA);
		_backgroundShaderNormal.setUniform("b", _NormalB);
		_backgroundShaderNormal.setUniform("c", _NormalC);
		_backgroundShaderNormal.setUniform("d", _NormalD);
		_backgroundStates.shader = &_backgroundShaderNormal;
		(tickCount % 2 == 0) ? _player->SetColor(sf::Color::Blue) : _player->SetColor(sf::Color::Magenta);
		_waveManager->SetMoveMultiplier(2.0f);
		_waveManager->SetEnemiesNextPosition();
		break;
	case BeatState::NORMAL2:
		_backgroundStates.shader = &_backgroundShaderNormal2;
		_waveManager->SetMoveMultiplier(2.0f);
		if (tickCount % 2 == 0) _waveManager->SetEnemiesNextPosition();
		break;
		//CASE SLOW : ONE ON TWO
	case BeatState::SLOW:
		_backgroundStates.shader = &_backgroundShaderSlow;
		_waveManager->SetMoveMultiplier(1.0f);
		if (tickCount % 2 == 0) _waveManager->SetEnemiesNextPosition();
		break;
		//CASE SLOW 2 : ONE ON TWO WITH S6
	case BeatState::SLOW2:
		_backgroundShaderSlow2.setUniform("cv", 0.5f);
		_backgroundStates.shader = &_backgroundShaderSlow2;
		_waveManager->SetMoveMultiplier(2.0f);
		if (tickCount % 2 == 0) _waveManager->SetEnemiesNextPosition();
		break;
	case BeatState::SLOW2_2:
		_backgroundShaderSlow2.setUniform("cv", 2.0f);
		_backgroundStates.shader = &_backgroundShaderSlow2;
		_waveManager->SetMoveMultiplier(2.0f);
		_waveManager->SetEnemiesNextPosition();
		break;
		//CASE BOSS : BOSS
	case BeatState::BOSS:
		_backgroundStates.shader = &_backgroundShaderBoss;
		_waveManager->SpawnBoss();
		break;
	case BeatState::BOSSSUBSTATE:
		_backgroundStates.shader = &_backgroundShaderBoss;
		_waveManager->SetMoveMultiplier(3.0f);
		_waveManager->SetEnemiesNextPosition();
		break;
		//CASE PAUSE : NO MOVEMENT
	case BeatState::PAUSE:
		_backgroundStates.shader = &_backgroundShaderPause;
		_waveManager->SetMoveMultiplier(0.0f);
		break;
	default:
		break;
	}
}

void RythmSystem::TweenCreationAndUpdate(float iTime) 
{
	switch (_actualState) {
	case BeatState::NORMAL:
		_backgroundShaderNormal.setUniform("iTime", iTime);
		break;
	case BeatState::NORMAL1_2:
		_backgroundShaderNormal.setUniform("iTime", iTime);
		break;
	case BeatState::NORMAL1_3:
		_backgroundShaderNormal.setUniform("iTime", iTime);
		break;
	case BeatState::NORMAL2:
		_backgroundShaderNormal2.setUniform("iTime", iTime);
		break;
	case BeatState::SLOW:
		_backgroundShaderSlow.setUniform("iTime", iTime);
		break;
	case BeatState::SLOW2:
		_backgroundShaderSlow2.setUniform("iTime", iTime);
		break;
	case BeatState::SLOW2_2:
		_backgroundShaderSlow2.setUniform("iTime", iTime);
		break;
	case BeatState::BOSS:
		_backgroundShaderBoss.setUniform("iTime", iTime);
		break;
	case BeatState::BOSSSUBSTATE:
		_backgroundShaderBoss.setUniform("iTime", iTime);
		break;
	case BeatState::PAUSE:
		_backgroundShaderPause.setUniform("iTime", iTime);
		break;
	}
}

void RythmSystem::Draw(RefsData data) 
{
	(*data.window).draw(_backgroundRect, _backgroundStates);
}
