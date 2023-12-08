#pragma once
#include "RefsData.h"
#include "Button.h"

class UIManager
{
public:
	UIManager(RefsData data);
	void DrawStartMenu(RefsData data);
	void DrawEndMenu(RefsData data);
	Button* GetStartButton();
	Button* GetQuitButton();
	Button* GetExitButton();
private:
	//StartMenu
	sf::Text _title;
	Button* _startButton;
	Button* _quitButton;

	//EndMenu
	sf::Text _endTitle;
	Button*_exitButton;
	sf::RectangleShape _endBackground;
};