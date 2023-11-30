#include "Background.h"

sf::Color ChangeBackground(int numb) {
	srand((unsigned)time(NULL));
	int finalCol = numb;
	
	std::cout << finalCol;
	switch (finalCol)
	{
	case 0:
		return sf::Color::Blue;
	case 1:
		return sf::Color::Red;
	case 2:
		return sf::Color::Green;
	default:
		break;
	}
}