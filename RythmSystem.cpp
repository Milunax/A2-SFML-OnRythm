#include "RythmSystem.h"

enum State
{
	NONE,
	NORMAL,
	SLOW,
	PAUSE,
	BOSS	
};



State GetStateOfBeat(std::map<int, State> lvl, int beat, State actualState) {
	for (auto element : lvl) {
		if (element.first == beat) {
			return element.second;
		}
	}
	return actualState;
}



