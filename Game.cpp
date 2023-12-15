#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <array>
#include "RythmSystem.h"
#include "Background.h"
#include "HealthBar.h"
#include "WaveManager.h"
#include "RefsData.h"
#include "BulletManager.h"
#include "GameManager.h"
#include "Button.h"
#include "Utils.h"
#include "UpgradeManager.h"
#include "RythmSystem.h"
#include "UIManager.h"
#include "WeaponManager.h"
#include "ParticleSystem.h"

void Game() 
{
	// SetUp
	RefsData data;
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Rythm");
	window.setVerticalSyncEnabled(true);
	sf::Font font;
	font.loadFromFile("../Assets/Technocra.ttf");
	data.window = &window;
	data.baseFont = &font;

	sf::Clock frameClock;
	data.frameClock = &frameClock;

	float bpm = 150.0f;
	float tick = 1 / (bpm / 60);
	float countTick = 0.0f;
	int tickCount = 0;

	sf::Music music;
	music.openFromFile("../sound/150.wav");
	data.music = &music;


	///Objects
	float iTime = 0.0;

	Player player(sf::Color::Blue, sf::Vector2f(590, 260), 50, 100, 200, 10.0f, 1.0f, 1.0f, 1.0f, 1.2f, 0);

	// Managers
	GameManager gameManager;
	RythmSystem rythmSystem(data);
	ParticleSystem particleSystem;
	UIManager uiManager(data, 0.05f);
	UpgradeManager upgradeManager(data);
	WaveManager waveManager(0.0f, 5.0f, 3, 32, 1.2f);
	BulletManager bulletManager;
	WeaponManager weaponManager;

	//Initialisation
	player.Init(&gameManager);
	gameManager.Init(data, &upgradeManager);
	rythmSystem.Init(&waveManager, &player, &gameManager);
	waveManager.Init(window, &gameManager, &player, &particleSystem);
	bulletManager.Init(&player, &waveManager, &uiManager);
	upgradeManager.Init(&player, &weaponManager, &uiManager);
	/*actualLVL = level_1;*/


	// Main Game
	while (window.isOpen())
	{

		float NormCT;
		float TweenNCT;
		// G�rer les �v�n�ments survenus depuis le dernier tour de boucle
		sf::Event event;
		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

		switch (gameManager.GetGameState())
		{
		case GameState::START_MENU:
			while (window.pollEvent(event))
			{
				// On g�re l'�v�n�ment
				switch (event.type)
				{
				case sf::Event::Closed:
					// L'utilisateur a cliqu� sur la croix => on ferme la fen�tre
					window.close();
					break;
				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						if (IsPointInsideRectangle(mousePos, uiManager.GetStartButton()->GetCollider()))
						{
							gameManager.StartGame();
						}
						if (IsPointInsideRectangle(mousePos, uiManager.GetQuitButton()->GetCollider()))
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
			// Remise au noir de toute la fen�tre
			window.clear();
			uiManager.DrawStartMenu(data);
			// On pr�sente la fen�tre sur l'�cran
			window.display();
			break;


		case GameState::IN_GAME:
			while (window.pollEvent(event))
			{
				// On g�re l'�v�n�ment
				switch (event.type)
				{
				case sf::Event::Closed:
					// L'utilisateur a cliqu� sur la croix => on ferme la fen�tre
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

				rythmSystem.ChangeSong(data, bpm, tick, tickCount);
				//std::cout << "COUNT : " << tickCount << std::endl;
				//std::cout << "STATE : " << actualState << std::endl;
				rythmSystem.MainSequence(tickCount);

				countTick -= tick;
			}

			//TweenCreation And Update
			NormCT = countTick / tick;
			TweenNCT = (1 - NormCT) * (1 - NormCT);
			iTime += TweenNCT * 0.01f;
			rythmSystem.TweenCreationAndUpdate(iTime);

			//Player/Wave/Bullet
			player.Update(data);
			waveManager.Update(data);
			bulletManager.Update(data);
			uiManager.Update(data);
			particleSystem.Update(data);

			// Affichage
			// Remise au noir de toute la fen�tre
			window.clear();
			//Background Shader
			rythmSystem.Draw(data);
			particleSystem.Draw(data);
			bulletManager.DrawBullets(data);
			player.Draw(data);
			waveManager.DrawAllEnemies(window);
			uiManager.DrawAllDamageTexts(data);
			gameManager.Draw(data);
			// On présente la fenétre sur l'�cran
			window.display();
			break;
			 


		case GameState::UPGRADES:
			while (window.pollEvent(event))
			{
				// On g�re l'�v�n�ment
				switch (event.type)
				{
				case sf::Event::Closed:
					// L'utilisateur a cliqu� sur la croix => on ferme la fen�tre
					window.close();
					break;
				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						if (IsPointInsideRectangle(mousePos, uiManager.GetUpgradeOneButton()->GetCollider()))
						{
							weaponManager.ApplyUpgrade(upgradeManager.GetUpgradeOne());
							waveManager.AugmentScaleFactor();
							gameManager.ResumeGame();
						}
						if (IsPointInsideRectangle(mousePos, uiManager.GetUpgradeTwoButton()->GetCollider()))
						{
							weaponManager.ApplyUpgrade(upgradeManager.GetUpgradeTwo());
							waveManager.AugmentScaleFactor();
							gameManager.ResumeGame();
						}
					}
				default:
					break;
				}
			}
			// Logique

			//Affichage
			window.clear();
			//Background Shader
			rythmSystem.Draw(data);
			particleSystem.Draw(data);
			bulletManager.DrawBullets(data);
			player.Draw(data);
			waveManager.DrawAllEnemies(window);
			uiManager.DrawAllDamageTexts(data);
			gameManager.Draw(data);
			uiManager.DrawUpgradeMenu(data);

			// On pr�sente la fen�tre sur l'�cran
			window.display();
			break;

		case GameState::END_OF_GAME:
			while (window.pollEvent(event))
			{
				// On g�re l'�v�n�ment
				switch (event.type)
				{
				case sf::Event::Closed:
					// L'utilisateur a cliqu� sur la croix => on ferme la fen�tre
					window.close();
					break;
				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						if (IsPointInsideRectangle(mousePos, uiManager.GetExitButton()->GetCollider()))
						{
							window.close();
						}
					}
					break;
				default:
					break;
				}
			}

			// Affichage
			// Remise au noir de toute la fen�tre
			window.clear();
			//Background Shader
			rythmSystem.Draw(data);
			bulletManager.DrawBullets(data);
			player.Draw(data);
			waveManager.DrawAllEnemies(window);
			gameManager.Draw(data);
			uiManager.DrawEndMenu(data);
			// On pr�sente la fen�tre sur l'�cran
			window.display();
			break;
		default:
			break;
		}


	}
}