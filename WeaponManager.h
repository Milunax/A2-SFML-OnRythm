#pragma once
#include "Weapon.h"
#include <array>
#include <iostream>

class WeaponManager
{
	public:
		WeaponManager();
		void Update();
		void Draw();
		bool HasWeapon(WeaponData weaponData);
		void ApplyUpgrade(WeaponData weaponData);
		void AddWeapon(WeaponData weaponData);
		void UpgradeWeapon(WeaponData weaponData);
	private:
		std::array<Weapon*, 3> _weapons;
};
