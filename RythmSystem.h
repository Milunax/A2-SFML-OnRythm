#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <map>

enum State;
State GetStateOfBeat(std::map<int, State> lvl, int beat, State actualState);


