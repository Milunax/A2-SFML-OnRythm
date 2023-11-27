#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

constexpr float cubeSpeed = 500.f;
float bpm = 150.0f;
float countTick = 0.0f;
float tick = 1 /(bpm / 60);

int main()
{
	// Initialisation

	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Rythm");
	window.setVerticalSyncEnabled(true);

	// Début de la boucle de jeu
	sf::RectangleShape rectangle;
	rectangle.setFillColor(sf::Color::Red);
	rectangle.setPosition(640, 360);
	rectangle.setSize(sf::Vector2f(128, 128));

	sf::Clock frameClock;
	int tickCount = 0;

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
		//std::cout << 1.0f / deltaTime << " FPS" << std::endl;


		if (countTick < tick) {
			countTick += deltaTime;
			//std::cout << countTick;
		}
		else {
			tickCount++;
			std::cout << (((tickCount % 4) == 0) ? "TOP" : "TIP");
			countTick -= tick;
		}

		// Logique
		sf::Vector2f pos = rectangle.getPosition();
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			pos.x = pos.x - deltaTime * cubeSpeed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			pos.x = pos.x + deltaTime * cubeSpeed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			pos.y = pos.y - deltaTime * cubeSpeed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			pos.y = pos.y + deltaTime * cubeSpeed;

		rectangle.setPosition(pos);

		// Affichage
		
		// Remise au noir de toute la fenêtre
		window.clear();

		// Tout le rendu va se dérouler ici
		window.draw(rectangle);

		// On présente la fenêtre sur l'écran
		window.display();
	}
}
