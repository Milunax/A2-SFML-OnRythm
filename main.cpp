#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "RythmSystem.h"
#include "Background.h"
#include "HealthBar.h"
#include "WaveManager.h"
#include "RefsData.h"
#include "BulletManager.h"
#include "GameManager.h"
#include "Button.h"
#include "Utils.h"

constexpr float cubeSpeed = 500.f;
float bpm = 150.0f;
float countTick = 0.0f;
float tick = 1 /(bpm / 60);
int tickCount = 0;

sf::Color backgroundColor;



std::map<int, State> level_1 = { {32, State::NORMAL}, {192,State::PAUSE} , {223,State::SLOW}, {288, State::BOSS} };
State actualState = State::SLOW;

// Sound
sf::Music music;

int main()
{
	// SetUp
	RefsData data;
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Rythm");
	window.setVerticalSyncEnabled(true);
	sf::Font font;
	font.loadFromFile("../Assets/Technocra.ttf");
	data.window = &window;
	data.baseFont = &font;

	///Objects
	//SHADERS
	//Load
	sf::Shader backgroundShaderNormal;
	sf::Shader backgroundShaderSlow;
	sf::Shader backgroundShaderBoss;
	sf::Shader backgroundShaderPause;

	backgroundShaderNormal.loadFromFile("Background.vert", "Background.frag");
	backgroundShaderSlow.loadFromFile("Background2.vert", "Background2.frag");
	backgroundShaderBoss.loadFromFile("Background.vert", "Background3.frag");
	backgroundShaderPause.loadFromFile("Background.vert", "Background4.frag");

	//Unifom
	backgroundShaderNormal.setUniform("iResolution", sf::Vector2f(window.getSize()));
	backgroundShaderSlow.setUniform("iResolution", sf::Vector2f(window.getSize()));
	backgroundShaderBoss.setUniform("iResolution", sf::Vector2f(window.getSize()));
	backgroundShaderPause.setUniform("iResolution", sf::Vector2f(window.getSize()));
	float iTime = 0.0;

	//Background
	sf::RectangleShape backgroundRect;
	backgroundRect.setPosition(0, 0);
	backgroundRect.setSize(sf::Vector2f(window.getSize()));
	sf::RenderStates backgroundStates;
	
	Player player(sf::Color::Blue, sf::Vector2f(590,260), 50, 100, 200);

	// Managers
	GameManager gameManager;
	WaveManager waveManager(0.0f, 5.0f, 3, 32);
	BulletManager bulletManager;

	//StartMenu
	sf::Text title = CreateTextAlone(*data.window, sf::Vector2f(640.0f, 100.0f), *data.baseFont, "Epileptik Rythm", 80, sf::Text::Bold);
	Button startButton(basicButton, data, sf::Vector2f(640.0f, 300.0f), "START");
	Button quitButton(basicButton, data, sf::Vector2f(640.0f, 410.0f), "QUIT");

	//Initialisation
	player.Init(&gameManager);
	waveManager.Init(window, &player);
	bulletManager.Init(&player, &waveManager);


	sf::Clock frameClock;

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
							frameClock.restart().asSeconds();
							if (!music.openFromFile("../sound/150.wav"))
								return -1; // error
							music.play();
							music.setLoop(true);
							backgroundStates.shader = &backgroundShaderSlow;
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
				//std::cout << "COUNT : " << tickCount << std::endl;

				actualState = GetStateOfBeat(level_1, tickCount, actualState);
				//std::cout << "STATE : " << actualState << std::endl;

				// MAIN SEQUENCE//
				switch (actualState)
				{
				case State::NONE:
					//std::cout << "lol" << std::endl;
					break;
				//CASE NORMAL : ON BEAT
				case State::NORMAL:
					backgroundStates.shader = &backgroundShaderNormal;
					(tickCount % 2 == 0) ? player.SetColor(sf::Color::Blue) : player.SetColor(sf::Color::Magenta);
					waveManager.SetEnemiesNextPosition();
					break;
				//CASE SLOW : ONE ON TWO
				case State::SLOW:
					backgroundStates.shader = &backgroundShaderSlow;
					if (tickCount % 2 == 0) waveManager.SetEnemiesNextPosition();
					break;
				//CASE SLOW : ONE ON TWO
				case State::BOSS:
					backgroundStates.shader = &backgroundShaderBoss;
					if (tickCount % 2 == 0) waveManager.SetEnemiesNextPosition();
					break;
				//CASE PAUSE : NO MOVEMENT
				case State::PAUSE:
					backgroundStates.shader = &backgroundShaderPause;
					break;
				default:
					break;
				}
				//*MAIN SEQUENCE//

				countTick -= tick;
			}

			//TweenCreation And Update
			NormCT = countTick / tick;
			TweenNCT = (1 - NormCT) * (1 - NormCT);
			iTime += TweenNCT * 0.01f;
			switch (actualState) {
			case State::NORMAL:
				backgroundShaderNormal.setUniform("iTime", iTime);
				break;
			case State::SLOW:
				backgroundShaderSlow.setUniform("iTime", iTime);
				break;
			case State::BOSS:
				backgroundShaderBoss.setUniform("iTime", iTime);
				break;
			case State::PAUSE:
				backgroundShaderPause.setUniform("iTime", iTime);
				break;
			}
			


			//Player/Wave/Bullet
			player.Update(data);
			waveManager.Update(data);
			bulletManager.Update(data);

			// Affichage
			// Remise au noir de toute la fenêtre
			window.clear();
			//Background Shader
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
