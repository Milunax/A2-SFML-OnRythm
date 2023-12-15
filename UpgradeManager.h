#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "RefsData.h"
#include "Player.h"
#include "WeaponManager.h"
#include "UIManager.h"

class UpgradeManager
{
	public:
		UpgradeManager(RefsData data);
		void Init(Player* player, WeaponManager* weaponManager, UIManager* uiManager);
		WeaponData GenerateUpgrade();
		void GenerateNewUpgrades();
		WeaponData GetUpgradeOne();
		WeaponData GetUpgradeTwo();

	private:
		WeaponData _upgradeOne;
		WeaponData _upgradeTwo;

		Player* _player;
		WeaponManager* _weaponManager;
		UIManager* _uiManager;
};
