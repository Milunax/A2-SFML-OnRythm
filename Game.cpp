#include "Game.h"

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

	Player player(sf::Color::Blue, sf::Vector2f(590, 260), 50, 100, 200);

	// Managers
	GameManager gameManager;
	RythmSystem rythmSystem(data);
	UpgradeManager upgradeManager(data);
	WaveManager waveManager(0.0f, 5.0f, 3, 32, 1.2f);
	BulletManager bulletManager;

	//StartMenu
	sf::Text title = CreateTextAlone(*data.window, sf::Vector2f(640.0f, 100.0f), *data.baseFont, "Epileptik Rythm", 80, sf::Text::Bold);
	Button startButton(basicButton, data, sf::Vector2f(640.0f, 300.0f), "START");
	Button quitButton(basicButton, data, sf::Vector2f(640.0f, 410.0f), "QUIT");

	//Initialisation
	player.Init(&gameManager);
	gameManager.Init(data, &upgradeManager);
	rythmSystem.Init(&waveManager, &player);
	waveManager.Init(window, &player);
	bulletManager.Init(&player, &waveManager);
	/*actualLVL = level_1;*/


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
				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						if (IsPointInsideRectangle(mousePos, startButton.GetCollider()))
						{
							gameManager.StartGame();
							//backgroundStates.shader = &backgroundShaderSlow;
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

			// Affichage
			// Remise au noir de toute la fenêtre
			window.clear();
			//Background Shader
			rythmSystem.Draw(data);
			/*window.draw(backgroundRect, backgroundStates);*/
			player.Draw(data);
			waveManager.DrawAllEnemies(window);
			bulletManager.DrawBullets(data);
			// On présente la fenêtre sur l'écran
			window.display();
			break;



		case GameState::UPGRADES:
			while (window.pollEvent(event))
			{
				// On gère l'événément
				switch (event.type)
				{
				case sf::Event::Closed:
					// L'utilisateur a cliqué sur la croix => on ferme la fenêtre
					window.close();
					break;
				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						if (IsPointInsideRectangle(mousePos, upgradeManager.GetUpgradeOneButton()->GetCollider()))
						{
							player.UpgradeStat(upgradeManager.GetUpgradeOne());
							waveManager.AugmentScaleFactor();
							gameManager.ResumeGame();
						}
						if (IsPointInsideRectangle(mousePos, upgradeManager.GetUpgradeTwoButton()->GetCollider()))
						{
							player.UpgradeStat(upgradeManager.GetUpgradeTwo());
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
			//window.draw(backgroundRect, backgroundStates);
			player.Draw(data);
			waveManager.DrawAllEnemies(window);
			bulletManager.DrawBullets(data);
			upgradeManager.DrawUpgradeMenu(data);

			// On présente la fenêtre sur l'écran
			window.display();
			break;

		default:
			break;
		}


	}
}