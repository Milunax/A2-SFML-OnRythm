#include "WeaponManager.h"

WeaponManager::WeaponManager() 
{
	_weapons = { nullptr, nullptr, nullptr };
}

void WeaponManager::Update() 
{
	
}

bool WeaponManager::HasWeapon(WeaponData weaponData)
{
	for (Weapon* weapon : _weapons) 
	{
		if (weapon == nullptr || weapon->GetName() != weaponData.Name) 
		{
			continue;
		}
		else if (weapon->GetName() == weaponData.Name) 
		{
			return true;
		}
	}

	return false;
}

void WeaponManager::ApplyUpgrade(WeaponData weaponData) 
{
	if (!HasWeapon(weaponData)) 
	{
		AddWeapon(weaponData);
	}
	else 
	{
		UpgradeWeapon(weaponData);
	}
}

void WeaponManager::AddWeapon(WeaponData weaponData)
{
	for (Weapon*& weapon : _weapons)
	{
		if (weapon == nullptr)
		{
			weapon = new Weapon(weaponData);
			std::cout << "Added : " + weapon->GetName() << std::endl;
			return;
		}
	}
}

void WeaponManager::UpgradeWeapon(WeaponData weaponData)
{
	for (Weapon* weapon : _weapons)
	{
		if (weapon == nullptr || weapon->GetName() != weaponData.Name) continue;
		if (weapon->GetName() == weaponData.Name) weapon->UpgradeWeapon();
	}
}