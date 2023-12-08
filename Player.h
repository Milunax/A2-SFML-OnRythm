#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include "RefsData.h"
#include "Collider.h"
#include "HealthBar.h"
#include "ExperienceBar.h"

class Bullet;
class GameManager;
enum class Upgrade;

class Player : public Entity {
	public :
		Player(sf::Color color, sf::Vector2f startPos, int radius, float maxHealth, float speed, float healthUpgradeValue, float baseDamage, float damagesUpgradeValue, 
				float bulletFireRate, float fireRateUpgradeValue, int timesWeaponUpgraded);
		void Init(GameManager* gameManager);
		void Draw(RefsData data);
		void TakeDamage(float value);
		void Die();
		sf::CircleShape& GetPlayerShape();
		void SetColor(sf::Color color);
		void Update(RefsData data);
		void Move(RefsData data);
		float GetRadius();
		CircleCollider GetCollider();
		sf::Vector2f GetOrientationDirection();
		void AddExperience(float value);
		void LevelUp();
		int GetLevel();
		float GetDamages();
		float GetFireRate();
		int GetTimesWeaponUpgraded();
		void UpgradeStat(Upgrade upgrade);

	private :
		ExperienceBar* _experienceBar;
		HealthBar* _healthBar;
		sf::CircleShape _circle;
		sf::Color _color;
		float _radius;
		sf::Vector2f _moveDirection = { 0, 0 };
		sf::Vector2f _orientationDirection = { 1, 0 };
		int _experience = 0;
		int _experienceToNextLevel;
		int _level;

		float _healthUpgradeValue;

		float _damages;
		float _damagesUpgradeValue;

		float _bulletFireRate;
		float _fireRateUpgradeValue;

		int _timesWeaponUpgraded;

		GameManager* _gameManager;
};