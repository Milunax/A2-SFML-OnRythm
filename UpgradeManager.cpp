#include "UpgradeManager.h"


UpgradeManager::UpgradeManager(RefsData data)
{
	_player = nullptr;
	_weaponManager = nullptr;
	_uiManager = nullptr;
}

void UpgradeManager::Init(Player* player, WeaponManager* weaponManager, UIManager* uiManager)
{
	_player = player;
	_weaponManager = weaponManager;
	_uiManager = uiManager;
}

WeaponData UpgradeManager::GenerateUpgrade()
{
	int random = rand() % _weaponDatabase.max_size();
	WeaponData weapon = _weaponDatabase[random];

	return weapon;
}

void UpgradeManager::GenerateNewUpgrades() 
{
	_upgradeOne = GenerateUpgrade();

	do
	{
		_upgradeTwo = GenerateUpgrade();
	} while (_upgradeTwo.Name == _upgradeOne.Name);

	_uiManager->SetButtonOneText(_upgradeOne);
	_uiManager->SetButtonTwoText(_upgradeTwo);

}

WeaponData UpgradeManager::GetUpgradeOne() 
{
	return _upgradeOne;
}

WeaponData UpgradeManager::GetUpgradeTwo()
{
	return _upgradeTwo;
}

