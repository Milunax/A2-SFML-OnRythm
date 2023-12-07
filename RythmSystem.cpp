#include "RythmSystem.h"
BeatState GetStateOfBeat(std::map<int, BeatState> lvl, int beat, BeatState actualState) {
	for (auto element : lvl) {
		if (element.first == beat) {
			return element.second;
		}
	}
	return actualState;
}



