#pragma once
#include "Weapon.h"
#include <array>
#include <iostream>
#include "RefsData.h"
#include "WaveManager.h"

class WeaponManager
{
	public:
		WeaponManager();
		void Init(Player* player, WaveManager* waveManager);
		void Update(RefsData data);
		void CheckAllCollisions();
		void Draw(RefsData data);
		bool HasWeapon(WeaponData weaponData);
		void ApplyUpgrade(WeaponData weaponData);
		void AddWeapon(WeaponData weaponData);
		void UpgradeWeapon(WeaponData weaponData);
	private:
		std::array<Weapon*, 3> _weapons;

		Player* _player;
		WaveManager* _waveManager;

};
