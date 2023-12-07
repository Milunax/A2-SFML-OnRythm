#include "RythmSystem.h"
State GetStateOfBeat(std::map<int, State> lvl, int beat, State actualState) {
	for (auto element : lvl) {
		if (element.first == beat) {
			return element.second;
		}
	}
	return actualState;
}



