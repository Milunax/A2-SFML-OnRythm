#include "Player.h"
#include "Bullet.h"
#include "Math.h"
#include "UpgradeManager.h"
#include "GameManager.h"

Player::Player(sf::Color color, sf::Vector2f startPos, float radius, float maxHealth, float speed, float healthUpgradeValue, float baseDamage, float damagesUpgradeValue, float baseBulletFireRate, float fireRateUpgradeValue, int timesWeaponUpgraded) : Entity(startPos, maxHealth, speed)
{
	_radius = radius;
	_color = color;
	_circle.setPosition(startPos);
	_experienceBar = new ExperienceBar(sf::Vector2f(640, 20), sf::Color::Green, sf::Vector2f(1000, 20));
	_healthBar = new HealthBar(sf::Vector2f(_position.x, _position.y + _radius + 20), sf::Color::Red, sf::Vector2f(_radius * 2, 10));
	_experienceToNextLevel = 10;
	_level = 1;
	_gameManager = nullptr;

	_healthUpgradeValue = healthUpgradeValue;

	_damages = baseDamage;
	_damagesUpgradeValue = damagesUpgradeValue;

	_bulletFireRate = baseBulletFireRate;
	_fireRateUpgradeValue = fireRateUpgradeValue;

	_timesWeaponUpgraded = timesWeaponUpgraded;
	//std::cout << _timesWeaponUpgraded << std::endl;

}

void Player::Init(GameManager* gameManager) 
{
	_gameManager = gameManager;
}

sf::CircleShape& Player::GetPlayerShape() 
{
	return _circle;
}

void Player::SetColor(sf::Color color) 
{
	_color = color;
}

void Player::Move(RefsData data)
{
	// Position avant le mouvement
	// std::cout << pos.x << " : " << pos.y << std::endl;

	_moveDirection = sf::Vector2f(0, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		_moveDirection.x = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
	{
		_moveDirection.x = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) 
	{
		_moveDirection.y = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
	{
		_moveDirection.y = 1;
	}

	Normalize(_moveDirection);
	//std::cout << _moveDirection.x << " : " << _moveDirection.y << std::endl;

	if (_moveDirection != sf::Vector2f(0, 0)) _orientationDirection = _moveDirection;

	_position = _position + _moveDirection * _speed * data.deltaTime;
	_position.x = std::clamp(_position.x, 0 + _radius, data.window->getSize().x - _radius);
	_position.y = std::clamp(_position.y, 0 + _radius, data.window->getSize().y - _radius);
	// Position apres le mouvement
	//std::cout << _position.x << " : " << _position.y << std::endl;
}

void Player::Update(RefsData data) 
{
	//std::cout << _experience << std::endl;
	//std::cout << data.deltaTime << std::endl;
	Move(data);
	
	_healthBar->UpdatePosition(sf::Vector2f(_position.x, _position.y + _radius + 20));

	if (_experience >= _experienceToNextLevel) {
		LevelUp();
	}
}

void Player::Draw(RefsData data)
{
	sf::CircleShape shape;
	shape.setOrigin(sf::Vector2f(_radius, _radius));
	shape.setRadius(_radius);
	shape.setFillColor(_color);
	shape.setPosition(_position);
	shape.setOutlineThickness(-3.0f);
	data.window->draw(shape);

	_experienceBar->Draw(data);
	_healthBar->Draw(data);
}

void Player::TakeDamage(float value)
{
	Entity::TakeDamage(value);

	//std::cout << _health << std::endl;
	_healthBar->UpdateSize(_health, _maxHealth);
}

void Player::Die() 
{
	_gameManager->ToEndState();
}

float Player::GetRadius() 
{
	return _radius;
}

CircleCollider Player::GetCollider() 
{
	CircleCollider collider = { _position, _radius };
	return collider;
}

sf::Vector2f Player::GetOrientationDirection()
{
	return _orientationDirection;
}

void Player::AddExperience(float value) {
	_experience += value;
	_experienceBar->UpdateSize(value, _experienceToNextLevel);
	//std::cout << _experience << std::endl;
}

void Player::LevelUp() {
	_level += 1;
	_experience = 0;
	_experienceBar->ResetSize();
	_experienceToNextLevel *= 1.5f;
	_experienceBar->UpdateLevel(_level);

	_gameManager->ToUpgradeState();
}

int Player::GetLevel() {
	return _level;
}

float Player::GetDamages()
{
	return _damages;
}

float Player::GetFireRate()
{
	return _bulletFireRate;
}

int Player::GetTimesWeaponUpgraded()
{
	return _timesWeaponUpgraded;
}