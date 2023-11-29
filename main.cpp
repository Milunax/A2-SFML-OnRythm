#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <list>
#include "Player.h"
#include "WaveManager.h"
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
	WaveManager waveManager(window, &player);

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

		player.Move(deltaTime);
		player.Shoot(deltaTime);
		waveManager.Update(deltaTime);

		// Affichage
		
		// Remise au noir de toute la fenêtre
		window.clear();

		// Tout le rendu va se dérouler ici
		player.Draw(window);
		waveManager.DrawAllEnemies(window);

		// On présente la fenêtre sur l'écran
		window.display();
	}
}
