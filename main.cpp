#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Background.h"
#include "Player.h"
#include "WaveManager.h"
#include "Data.h"
#include "BulletManager.h"
#include "GameManager.h"

constexpr float cubeSpeed = 500.f;
float bpm = 151.0f;
float countTick = 0.0f;
float tick = 1 /(bpm / 60);

sf::Color backgroundColor;

// Sound
sf::Music music;


int main()
{
	// Initialisation

	Data data;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Rythm");
	window.setVerticalSyncEnabled(true);

	data.window = &window;

	// Objects
	sf::RectangleShape rectangle;
	rectangle.setFillColor(sf::Color::Red);
	rectangle.setPosition(640, 360);
	rectangle.setSize(sf::Vector2f(128, 128));

	sf::CircleShape circle;
	circle.setFillColor(sf::Color::Transparent);
	circle.setPosition(640, 360);
	circle.setOutlineThickness(15);
	circle.setOutlineColor(sf::Color::Blue);
	circle.setRadius(100);
	int goalScale = 500;
	int resultScale = (float)circle.getRadius();
	
	Player player(sf::Color::Blue, sf::Vector2f(590,260), 50, 100, 200);
	WaveManager waveManager(window, &player);
	BulletManager bulletManager(&player, waveManager.GetEnemyList(), &waveManager);

	sf::Clock frameClock;
	int tickCount = 0;

	// Music buffer
	if (!music.openFromFile("../sound/150.wav"))
		return -1; // error
	music.play();
	music.setLoop(true);

	// Main Game
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

		data.deltaTime = frameClock.restart().asSeconds();
		//std::cout << 1.0f / deltaTime << " FPS" << std::endl;


		if (countTick < tick) {
			countTick += data.deltaTime;
			//std::cout << countTick;
		}
		else {
			tickCount++;
			/*
			std::cout << (((tickCount % 2) == 0) ? "TOP" : "TIP") << std::endl;
			std::cout << tickCount << std::endl;
			*/
			if (tickCount < 287) {
				if (tickCount == 1) waveManager.SpawnBoss();
				(tickCount % 2 == 0) ? rectangle.setFillColor(sf::Color::Yellow) : rectangle.setFillColor(sf::Color::Magenta);
				if (tickCount % 2 == 0) waveManager.SetEnemiesNextPosition();
				backgroundColor = ChangeBackground(tickCount % 3);
			}
			else {
				(tickCount % 2 == 0) ? rectangle.setFillColor(sf::Color::Green) : rectangle.setFillColor(sf::Color::Yellow);
				if (tickCount % 2 == 0) waveManager.SetEnemiesNextPosition();
			}
			countTick -= tick;
		}

		// Logique
		player.Update(data);

		waveManager.Update(data);

		bulletManager.Update(data);
		// Affichage
		/*
		resultScale = circle.getRadius();
		resultScale += (goalScale - resultScale) / 100; // increase division for stronger easing
		circle.setRadius(resultScale);
		*/
		// Remise au noir de toute la fenêtre
		window.clear();
		// Tout le rendu va se dérouler ici
		window.draw(rectangle);
		window.draw(circle);
		player.Draw(data);
		waveManager.DrawAllEnemies(window);
		bulletManager.DrawBullets(data);

		// On présente la fenêtre sur l'écran
		window.display();
	}
}
