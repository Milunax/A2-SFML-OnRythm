#include "Player.h"
#include "Bullet.h"

Player::Player(sf::Color color, sf::Vector2f startPos, int radius, float maxHealth, float speed) : Entity(startPos, maxHealth, speed)
{
	_radius = radius;
	_color = color;
	_circle.setPosition(startPos);
}

sf::CircleShape& Player::GetPlayerShape() 
{
	return _circle;
}

void Player::Move(float deltaTime) 
{
	// Position avant le mouvement
	// std::cout << pos.x << " : " << pos.y << std::endl;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		_position.x = _position.x - deltaTime * _speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		_position.x = _position.x + deltaTime * _speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		_position.y = _position.y - deltaTime * _speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		_position.y = _position.y + deltaTime * _speed;

	// Position apres le mouvement
	// std::cout << pos.x << " : " << pos.y << std::endl;

	_circle.setPosition(_position);
}

void Player::Update(float deltaTime, std::vector<Bullet*>& bulletList) 
{
	UpdateTimer(deltaTime);
	if (_fireTimer >= 1 / _bulletFireRate) {
		bulletList.push_back(Shoot());
		_fireTimer = 0.0f;
	}
}

void Player::UpdateTimer(float deltaTime) 
{
	_fireTimer += deltaTime;
	std::cout << _fireTimer << std::endl;
}

Bullet* Player::Shoot()
{
	Bullet* bullet = new Bullet(sf::Color::Yellow, 10, _position, sf::Vector2f{1, 0}, 50);
	std::cout << "a tiré" << std::endl;
	return bullet;
}

void Player::Draw(sf::RenderWindow& window)
{
	sf::CircleShape shape;
	shape.setRadius(_radius);
	shape.setFillColor(_color);
	shape.setPosition(_position);
	window.draw(shape);
}
