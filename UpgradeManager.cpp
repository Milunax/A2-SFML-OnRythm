#include "UpgradeManager.h"


UpgradeManager::UpgradeManager(RefsData data)
{
	_upgradeOne = Upgrade::HEALTH;
	_upgradeTwo = Upgrade::HEALTH;

	_player = nullptr;
}

void UpgradeManager::Init(Player* player)
{
	_player = player;
}

Upgrade UpgradeManager::GenerateUpgrade()
{
	int random = rand() % 4;
	Upgrade upgrade = (Upgrade)random;

	return upgrade;
}

void UpgradeManager::GenerateNewUpgrades() 
{
	if (_player->GetTimesWeaponUpgraded() >= 3)
	{

		do
		{
			_upgradeOne = GenerateUpgrade();
		} while (_upgradeOne == Upgrade::WEAPON);

		do
		{
			_upgradeTwo = GenerateUpgrade();
		} while (_upgradeTwo == Upgrade::WEAPON || _upgradeTwo == _upgradeOne);
	}
	else
	{
		_upgradeOne = GenerateUpgrade();

		do
		{
			_upgradeTwo = GenerateUpgrade();
		} while (_upgradeTwo == _upgradeOne);
	}
}

Upgrade UpgradeManager::GetUpgradeOne() 
{
	return _upgradeOne;
}

Upgrade UpgradeManager::GetUpgradeTwo()
{
	return _upgradeTwo;
}