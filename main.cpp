#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <list>
#include "Player.h"
#include "Enemy.h"
#include "EnemySpawner.h"

constexpr float cubeSpeed = 500.f;

int main()
{
	// Initialisation

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Geometry Wars");
	window.setVerticalSyncEnabled(true);

	// Début de la boucle de jeu
	//sf::RectangleShape rectangle;
	//rectangle.setFillColor(sf::Color::Red);
	//rectangle.setPosition(640, 360);
	//rectangle.setSize(sf::Vector2f(128, 128));
	Player player(sf::Color::Blue, sf::Vector2f(100, 100), 50, 100, 500);
	std::vector<Enemy*> enemyList;
	EnemySpawner enemySpawner(sf::Vector2f(900, 300), 0.5f);
	Enemy* enemy = enemySpawner.InstantiateEnemy(&player);

	sf::Clock frameClock;

	while (window.isOpen())
	{
		// Gérer les événéments survenus depuis le dernier tour de boucle
		sf::Event event;
		while (window.pollEvent(event))
		{
			// On gère l'événément
			switch (event.type)
			{
				case sf::Event::Closed:
					// L'utilisateur a cliqué sur la croix => on ferme la fenêtre
					window.close();
					break;

				default:
					break;
			}
		}

		float deltaTime = frameClock.restart().asSeconds();
		//std::cout << 1.f / deltaTime << " FPS" << std::endl;

		// Logique
		enemySpawner.Update(deltaTime, enemyList, &player);
		std::cout << enemyList.size() << std::endl;

		player.Move(deltaTime);
		player.Shoot(deltaTime);

		for (Enemy* en : enemyList) {
			en->Move(deltaTime);
		}

		// Affichage
		
		// Remise au noir de toute la fenêtre
		window.clear();

		// Tout le rendu va se dérouler ici
		player.Draw(window);
		for (Enemy* en : enemyList) {
			en->Draw(window);
		}

		// On présente la fenêtre sur l'écran
		window.display();
	}
}
