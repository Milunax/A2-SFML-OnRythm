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
	SLOW,
	PAUSE,
	BOSS
};
BeatState GetStateOfBeat(std::map<int, BeatState> lvl, int beat, BeatState actualState);


