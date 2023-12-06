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
#include "Button.h"

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
	if (!sf::Shader::isAvailable()) {
		std::cout << "amdn";
	}
	else {
		backgroundShader.loadFromFile("Background.vert", "Background.frag");
	}
	backgroundShader.setUniform("iResolution", sf::Vector2f(window.getSize()));
	float iTime = 0.0;

	sf::RectangleShape backgroundRect;
	backgroundRect.setPosition(0, 0);
	backgroundRect.setSize(sf::Vector2f(window.getSize()));
	sf::RenderStates backgroundStates;
	backgroundStates.shader = &backgroundShader;
	
	Player player(sf::Color::Blue, sf::Vector2f(590,260), 50, 100, 200);

	// Managers
	GameManager gameManager;

	WaveManager waveManager(window, &player);
	BulletManager bulletManager(&player, waveManager.GetEnemyList(), &waveManager);

	//StartMenu
	sf::Font arial;
	arial.loadFromFile("../Assets/ARIAL.TTF");

	sf::Text title;
	title.setFont(arial);
	title.setString("Epileptik Rythm");
	title.setCharacterSize(80);
	title.setStyle(sf::Text::Bold);
	title.setPosition(sf::Vector2f(350,100));

	Button startButton(basicButton, sf::Vector2f(640, 300), arial, "START");
	Button quitButton(basicButton, sf::Vector2f(640, 410), arial, "QUIT");

	sf::Clock frameClock;

	// Music buffer
	if (!music.openFromFile("../sound/150.wav"))
		return -1; // error
	music.play();
	music.setLoop(true);

	// Main Game
	while (window.isOpen())
	{
		float NormCT;
		float TweenNCT;
		// Gérer les événéments survenus depuis le dernier tour de boucle
		sf::Event event;
		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

		switch (gameManager.GetGameState())
		{
		case GameState::START_MENU:
			while (window.pollEvent(event))
			{
				// On gère l'événément
				switch (event.type)
				{
				case sf::Event::Closed:
					// L'utilisateur a cliqué sur la croix => on ferme la fenêtre
					window.close();
					break;
				case sf::Event::MouseButtonPressed :
					if (event.mouseButton.button == sf::Mouse::Left) 
					{
						if (IsPointInsideRectangle(mousePos, startButton.GetCollider())) 
						{
							gameManager.SetGameState(GameState::IN_GAME);
						}
						if (IsPointInsideRectangle(mousePos, quitButton.GetCollider()))
						{
							window.close();
						}
					}
					break;
				default:
					break;
				}
			}
			//Logique


			// Affichage
			// Remise au noir de toute la fenêtre
			window.clear();
			window.draw(title);
			startButton.Draw(data);
			quitButton.Draw(data);
			// On présente la fenêtre sur l'écran
			window.display();
			break;


		case GameState::IN_GAME:
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

			// Logique

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
					if (tickCount % 2 == 0) waveManager.SetEnemiesNextPosition();
					backgroundColor = ChangeBackground(tickCount % 3);
					break;
				case State::SLOW:
					if (tickCount % 2 == 0) waveManager.SetEnemiesNextPosition();
					break;
				default:
					break;
				}
				countTick -= tick;
			}
			NormCT = countTick / tick;
			TweenNCT = (1 - NormCT) * (1 - NormCT);
			iTime += TweenNCT * 0.01f;
			backgroundShader.setUniform("iTime", iTime);

			player.Update(data);
			waveManager.Update(data);
			bulletManager.Update(data);

			// Affichage
			// Remise au noir de toute la fenêtre
			window.clear();
			window.draw(backgroundRect, backgroundStates);
			player.Draw(data);
			waveManager.DrawAllEnemies(window);
			bulletManager.DrawBullets(data);
			// On présente la fenêtre sur l'écran
			window.display();
			break;

		default:
			break;
		}

		
	}
}
