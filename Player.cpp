#include "Player.h"
#include "Bullet.h"
#include "Math.h"

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

void Player::SetColor(sf::Color color) 
{
	_color = color;
}

void Player::Move(Data data)
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
	// Position apres le mouvement
	//std::cout << _position.x << " : " << _position.y << std::endl;
}

void Player::Update(Data data) 
{
	//std::cout << data.deltaTime << std::endl;
	Move(data);
	UpdateTimer(data);
	if (_fireTimer >= 1 / _bulletFireRate) {
		_bulletList.push_back(Shoot());
		std::cout << _bulletList.size() << std::endl;
		_fireTimer = 0.0f;
	}

	UpdateBullets(data);
}

void Player::UpdateTimer(Data data) 
{
	_fireTimer += data.deltaTime;
	//std::cout << _fireTimer << std::endl;
}

Bullet* Player::Shoot()
{
	Bullet* bullet = new Bullet(sf::Color::Yellow, 10, _position, _orientationDirection, 1000);
	//std::cout << "a tiré" << std::endl;
	return bullet;
}

void Player::Draw(Data data)
{
	sf::CircleShape shape;
	shape.setOrigin(sf::Vector2f(_radius, _radius));
	shape.setRadius(_radius);
	shape.setFillColor(_color);
	shape.setPosition(_position);
	data.window->draw(shape);
}

void Player::DrawBullets(Data data) {
	for (Bullet* bullet : _bulletList) {
		bullet->Draw(*data.window);
	}
}

void Player::UpdateBullets(Data data) 
{
	for (Bullet* bullet : _bulletList) {
		bullet->CheckPosition(data, _bulletList);
		bullet->Move(data.deltaTime);
	}
}

float Player::GetRadius() 
{
	return _radius;
}