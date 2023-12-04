#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "RythmSystem.h"
#include "Background.h"
#include "HealthBar.h"
#include "WaveManager.h"
#include "Data.h"
#include "BulletManager.h"
#include "GameManager.h"

constexpr float cubeSpeed = 500.f;
float bpm = 150.0f;
float countTick = 0.0f;
float tick = 1 /(bpm / 60);
int tickCount = 0;

sf::Color backgroundColor;



std::map<int, State> level_1 = { {10, State::SLOW}, {30,State::NORMAL} };
State actualState = State::NORMAL;

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
	sf::Shader backgroundShader;
	backgroundShader.loadFromFile("Background.vert", "Background.frag");
	backgroundShader.setUniform("iResolution", sf::Vector2f(window.getSize()));
	float iTime = 0.0;
	sf::RectangleShape rectangle;
	rectangle.setFillColor(sf::Color::Red);
	rectangle.setPosition(640, 360);
	rectangle.setSize(sf::Vector2f(128, 128));

	sf::RectangleShape backgroundRect;
	backgroundRect.setPosition(0, 0);
	backgroundRect.setSize(sf::Vector2f(window.getSize()));
	sf::RenderStates backgroundStates;
	backgroundStates.shader = &backgroundShader;




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



		countTick += data.deltaTime;

		if (countTick >= tick) {
			tickCount++;
			std::cout << "COUNT : " << tickCount << std::endl;

			actualState = GetStateOfBeat(level_1, tickCount, actualState);
			std::cout << "STATE : " << actualState << std::endl;

			switch (actualState)
			{
			case State::NONE:
				std::cout << "lol" << std::endl;
				break;
			case State::NORMAL:
				(tickCount % 2 == 0) ? player.SetColor(sf::Color::Blue) : player.SetColor(sf::Color::Magenta);
				waveManager.MoveAllEnemies(data.deltaTime);
				backgroundColor = ChangeBackground(tickCount % 3);
				break;
			case State::SLOW:
				if (tickCount % 2 == 0) waveManager.MoveAllEnemies(data.deltaTime);
				if (tickCount % 2 == 0) waveManager.SetEnemiesNextPosition();
				break;
			default:
				break;
			}
			countTick -= tick;
		}
		float NormCT = countTick / tick;
		float TweenNCT = (1 - NormCT) * (1 - NormCT);
		iTime += TweenNCT * 0.01f;
		backgroundShader.setUniform("iTime", iTime);

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
		window.draw(backgroundRect, backgroundStates);
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
