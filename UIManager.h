#pragma once
#include "RefsData.h"
#include "Button.h"
#include <vector>
#include <algorithm>

class UIManager
{
public:
	UIManager(RefsData data, float lowerTransparencyTime);
	void DrawStartMenu(RefsData data);
	std::vector<sf::Text*>* GetDamageTextList();
	void Update(RefsData data);
	void UpdateAllDamageTexts(RefsData data);
	void DrawAllDamageTexts(RefsData data);
	void EraseOldTexts();
	void DrawEndMenu(RefsData data);
	Button* GetStartButton();
	Button* GetQuitButton();
	Button* GetExitButton();
private:
	//StartMenu
	sf::Text _title;
	Button* _startButton;
	Button* _quitButton;

	//DamageTexts
	std::vector<sf::Text*> _allDamageTexts;
	float _timer;
	float _lowerTransparencyTime;

	//EndMenu
	sf::Text _endTitle;
	Button*_exitButton;
	sf::RectangleShape _endBackground;
};