#include "WeaponManager.h"
#include "CircularWeapon.h"
#include "CloseWeapon.h"
#include "BasicWeapon.h"

WeaponManager::WeaponManager() 
{
	BasicWeapon* basic = new BasicWeapon(2.0f, 1.0f, _pistol);
	CloseWeapon* close = new CloseWeapon(sf::Color(255, 255, 255, 100), 75.0f, 2.0f, 1.0f, _area);
	CircularWeapon* circular = new CircularWeapon(125.0f, 2.0f, 1, 1.0f, _graviton);
	_weapons = { basic, nullptr, nullptr };

	_player = nullptr;
	_waveManager = nullptr;
}

void WeaponManager::Init(Player* player, WaveManager* waveManager)
{
	_player = player;
	_waveManager = waveManager;
}

void WeaponManager::Update(RefsData data) 
{
	for (Weapon* weapon : _weapons) 
	{
		if(weapon != nullptr)weapon->Update(data, _player);
	}
	CheckAllCollisions(data);

}

void WeaponManager::CheckAllCollisions(RefsData data)
{
	for (Weapon* weapon : _weapons) 
	{
		if (weapon != nullptr)weapon->CheckCollision(_waveManager->GetEnemyList());
	}
}

void WeaponManager::Draw(RefsData data)
{
	for (Weapon* weapon : _weapons) 
	{
		if (weapon != nullptr)weapon->Draw(data);
	}
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
			if(weaponData.Name == "Pistol") weapon = new BasicWeapon(2.0f, 1.0f, _pistol);
			if (weaponData.Name == "Area") weapon = new CloseWeapon(sf::Color(255, 255, 255, 100), 75.0f, 2.0f, 1.0f, _area);
			if(weaponData.Name == "Graviton") weapon = new CircularWeapon(125.0f, 2.0f, 1, 1.0f, _graviton);
			if (weapon != nullptr) 
			{
				std::cout << "Added : " + weapon->GetName() << std::endl;
			}
			else 
			{
				std::cout << "Error when adding weapon"<< std::endl;
			}
			
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