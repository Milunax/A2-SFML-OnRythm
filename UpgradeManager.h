#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Button.h"
#include "RefsData.h"
#include "Player.h"

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
		void Init(Player* player);
		Upgrade GenerateUpgrade();
		void GenerateNewUpgrades();
		void SetUpgradeButtonText(Button* button, Upgrade upgrade);
		Upgrade GetUpgradeOne();
		Upgrade GetUpgradeTwo();

	private:
		Upgrade _upgradeOne;
		Upgrade _upgradeTwo;

		Player* _player;
};
