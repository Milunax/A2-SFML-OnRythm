#pragma once
#include "RefsData.h"
#include "Button.h"
#include <vector>
#include <algorithm>
#include "Weapon.h"

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
	void DrawUpgradeMenu(RefsData data);
	void DrawEndMenu(RefsData data);
	Button* GetStartButton();
	Button* GetQuitButton();
	Button* GetUpgradeOneButton();
	void SetButtonOneText(WeaponData weaponData);
	Button* GetUpgradeTwoButton();
	void SetButtonTwoText(WeaponData weaponData);
	Button* GetExitButton();
private:
	//StartMenu
	sf::Text _title;
	sf::Image _logoImage;
	sf::Texture _logoTexture;
	sf::Sprite _logoSprite;
	Button* _startButton;
	Button* _quitButton;

	//DamageTexts
	std::vector<sf::Text*> _allDamageTexts;
	float _timer;
	float _lowerTransparencyTime;

	//UpgradeMenu
	Button* _upgradeOneButton;
	Button* _upgradeTwoButton;

	//EndMenu
	sf::Text _endTitle;
	Button*_exitButton;
	sf::RectangleShape _endBackground;
};