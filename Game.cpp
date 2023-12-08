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
	music.openFromFile("../sound/2.wav");
	data.music = &music;


	///Objects
	float iTime = 0.0;

	Player player(sf::Color::Blue, sf::Vector2f(590, 260), 50, 100, 200, 10.0f, 1.0f, 1.0f, 1.0f, 2.5f, false);

	// Managers
	GameManager gameManager;
	RythmSystem rythmSystem(data);
	UIManager uiManager(data);
	UpgradeManager upgradeManager(data);
	WaveManager waveManager(0.0f, 5.0f, 3, 32, 1.2f);
	BulletManager bulletManager;

	//EndMenu
	sf::Text endTitle = CreateTextAlone(*data.window, sf::Vector2f(640.0f, 200.0f), *data.baseFont, "Game Over", 80, sf::Text::Bold);
	Button exitButton(basicButton, data, sf::Vector2f(640.0f, 360.0f), "EXIT");
	sf::RectangleShape endBackground;
	endBackground.setSize(sf::Vector2f((float)(*data.window).getSize().x, (float)(*data.window).getSize().y));
	sf::Color bgColor(0, 0, 0, 120);
	endBackground.setFillColor(bgColor);
	endBackground.setPosition(sf::Vector2f(0, 0));

	//Initialisation
	player.Init(&gameManager);
	gameManager.Init(data, &upgradeManager);
	rythmSystem.Init(&waveManager, &player);
	waveManager.Init(window, &gameManager, &player);
	bulletManager.Init(&player, &waveManager);


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

			// Affichage
			// Remise au noir de toute la fen�tre
			window.clear();
			//Background Shader
			rythmSystem.Draw(data);
			player.Draw(data);
			waveManager.DrawAllEnemies(window);
			bulletManager.DrawBullets(data);
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
			player.Draw(data);
			waveManager.DrawAllEnemies(window);
			bulletManager.DrawBullets(data);
			gameManager.Draw(data);
			upgradeManager.DrawUpgradeMenu(data);

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
				default:
					break;
				}
			}

			// Affichage
			// Remise au noir de toute la fen�tre
			window.clear();
			//Background Shader
			rythmSystem.Draw(data);
			player.Draw(data);
			waveManager.DrawAllEnemies(window);
			bulletManager.DrawBullets(data);
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