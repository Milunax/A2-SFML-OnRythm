#include "RythmSystem.h"


enum State
{
	PAUSE,
	NORMAL,
	SLOW,
	BOSS	
};

std::map<int, State> level_1 = { {19, PAUSE}, {25,NORMAL} };

State GetStateOfBeat(std::map<int, State> lvl, int beat) {
	for (auto element : lvl) {
		if (element.first == beat) {
			return element.second;
		}
	}
}


