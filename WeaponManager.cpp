#include "WeaponManager.h"
#include "CircularWeapon.h"
#include "CloseWeapon.h"
#include "BasicWeapon.h"

WeaponManager::WeaponManager() 
{
	BasicWeapon* basic = new BasicWeapon(2.0f, 1.0f, _range);
	sf::Color color(255, 255, 255, 100);
	CloseWeapon* close = new CloseWeapon(color, 200.0f, 2.0f, 1.0f, _close);
	CircularWeapon* circular = new CircularWeapon(200.0f, 2.0f, 1, 10.0f, _book);
	_weapons = { basic, close, circular };

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
	CheckAllCollisions();

}

void WeaponManager::CheckAllCollisions()
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
			//weapon = new Weapon(10, 1 ,weaponData);
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