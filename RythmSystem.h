#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <map>

enum BeatState
{
	NONE,
	NORMAL,
	NORMAL1_2,
	NORMAL1_3,
	NORMAL2,
	SLOW,
	SLOW2,
	PAUSE,
	BOSS,
	BOSSSUBSTATE
};

BeatState GetStateOfBeat(std::map<int, BeatState> lvl, int beat, BeatState actualState);



