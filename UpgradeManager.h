#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Button.h"
#include "RefsData.h"

enum class Upgrade
{
	HEALTH,
	ATTACK,
	ATTACKSPEED,
	WEAPON
};

class UpgradeManager
{
	public:
		UpgradeManager(RefsData data);
		Upgrade GenerateUpgrade();
		void GenerateNewUpgrades();
		void SetUpgradeButtonText(Button* button, Upgrade upgrade);
		void DrawUpgradeMenu(RefsData data);
		Button* GetUpgradeOneButton();
		Button* GetUpgradeTwoButton();
	private:
		Upgrade _upgradeOne;
		Upgrade _upgradeTwo;

		Button* _upgradeOneButton;
		Button* _upgradeTwoButton;
};
