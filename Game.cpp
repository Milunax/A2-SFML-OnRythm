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

	sf::Color backgroundColor;
	std::map<int, BeatState> level_1 = { 
		{32, BeatState::NORMAL}, 
		{64, BeatState::NORMAL1_2}, 
		{128, BeatState::NORMAL1_3},
		{192,BeatState::PAUSE} , 
		{223,BeatState::SLOW}, 
		{288, BeatState::BOSS}, 
		{289, BeatState::BOSSSUBSTATE} ,
		{320, BeatState::BOSS},
		{321, BeatState::BOSSSUBSTATE} ,
		{352, BeatState::NORMAL},
		{384, BeatState::NORMAL1_2},
		{416,BeatState::PAUSE}
	};
	std::map<int, BeatState> level_2 = {
		{0, BeatState::NORMAL2},
		{64, BeatState::NORMAL},
		{124,BeatState::PAUSE} ,
		{128,BeatState::SLOW2},
		{224, BeatState::BOSS} ,
		{225, BeatState::BOSSSUBSTATE} ,
		{288, BeatState::SLOW} ,
		{320, BeatState::NORMAL} ,
	};
	std::map<int, BeatState> level_3 = { {32, BeatState::NORMAL}, {192,BeatState::PAUSE} , {223,BeatState::SLOW}, {288, BeatState::BOSS} };
	std::array<std::map<int, BeatState>, 3> levelArray = { level_1, level_2, level_3 };
	std::map<int, BeatState> actualLVL;
	int actualLVLCount = 0;
	BeatState actualState = BeatState::SLOW;

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
	//SHADERS
	//Load
	sf::Shader backgroundShaderNormal;
	sf::Shader backgroundShaderNormal2;
	sf::Shader backgroundShaderSlow;
	sf::Shader backgroundShaderSlow2;
	sf::Shader backgroundShaderBoss;
	sf::Shader backgroundShaderPause;

	backgroundShaderNormal.loadFromFile("Background.vert", "Background.frag");
	backgroundShaderNormal2.loadFromFile("Background.vert", "Background7.frag");
	backgroundShaderSlow.loadFromFile("Background2.vert", "Background2.frag");
	backgroundShaderSlow2.loadFromFile("Background2.vert", "Background6.frag");
	backgroundShaderBoss.loadFromFile("Background.vert", "Background3.frag");
	backgroundShaderPause.loadFromFile("Background.vert", "Background4.frag");

	//Unifom
	backgroundShaderNormal.setUniform("iResolution", sf::Vector2f(window.getSize()));
	backgroundShaderNormal2.setUniform("iResolution", sf::Vector2f(window.getSize()));
	backgroundShaderSlow.setUniform("iResolution", sf::Vector2f(window.getSize()));
	backgroundShaderSlow2.setUniform("iResolution", sf::Vector2f(window.getSize()));
	backgroundShaderBoss.setUniform("iResolution", sf::Vector2f(window.getSize()));
	backgroundShaderPause.setUniform("iResolution", sf::Vector2f(window.getSize()));
	sf::Vector3f NormalA = {0.172, 0.215, 0.947 };
	sf::Vector3f NormalB = { 0.385,0.967,0.336 };
	sf::Vector3f NormalC = { 0.813,0.299,0.804 };
	sf::Vector3f NormalD = { 1.869,5.081,2.817 };
	backgroundShaderNormal.setUniform("a", NormalA);
	backgroundShaderNormal.setUniform("b", NormalB);
	backgroundShaderNormal.setUniform("c", NormalC);
	backgroundShaderNormal.setUniform("d", NormalD);
	float iTime = 0.0;

	//Background
	sf::RectangleShape backgroundRect;
	backgroundRect.setPosition(0, 0);
	backgroundRect.setSize(sf::Vector2f(window.getSize()));
	sf::RenderStates backgroundStates;

	Player player(sf::Color::Blue, sf::Vector2f(590, 260), 50, 100.0f, 200.0f, 10.0f, 1.0f, 1.0f, 1.0f, 2.5f, false);

	// Managers
	GameManager gameManager;
	UpgradeManager upgradeManager(data);
	WaveManager waveManager(0.0f, 5.0f, 3, 32);
	BulletManager bulletManager;

	//StartMenu
	sf::Text title = CreateTextAlone(*data.window, sf::Vector2f(640.0f, 100.0f), *data.baseFont, "Epileptik Rythm", 80, sf::Text::Bold);
	Button startButton(basicButton, data, sf::Vector2f(640.0f, 300.0f), "START");
	Button quitButton(basicButton, data, sf::Vector2f(640.0f, 410.0f), "QUIT");

	//UpgradesMenu
	
	//Score
	sf::Text score = CreateTextAlone(*data.window, sf::Vector2f(50.0f, 20.0f), *data.baseFont, "Score : 0", 24, sf::Text::Regular);

	//Initialisation
	player.Init(&gameManager);
	gameManager.Init(data, &upgradeManager);
	waveManager.Init(window, &gameManager, &player);
	bulletManager.Init(&player, &waveManager);
	actualLVL = level_1;


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

				// Changing Song
				if (music.getStatus() == 0) {
					actualLVLCount++;
					actualLVL = levelArray[actualLVLCount];
					tickCount = 0;
					switch (actualLVLCount)
					{
					case 1:
						bpm = 145.0;
						tick = 1 / (bpm / 60);
						if (!music.openFromFile("../sound/145.wav"))
							return; // error
						music.play();
						break;
					case 2:
						bpm = 145.0;
						tick = 1 / (bpm / 60);
						if (!music.openFromFile("../sound/145.wav"))
							return; // error
						music.play();
						break;
					default:
						break;
					}
				}

				//std::cout << "COUNT : " << tickCount << std::endl;

				actualState = GetStateOfBeat(actualLVL, tickCount, actualState);
				//std::cout << "STATE : " << actualState << std::endl;
				 
				// MAIN SEQUENCE//
				switch (actualState)
				{
				case BeatState::NONE:
					std::cout << "lol" << std::endl;
					break;
					//CASE NORMAL : ON BEAT
				case BeatState::NORMAL:
					backgroundStates.shader = &backgroundShaderNormal;
					(tickCount % 2 == 0) ? player.SetColor(sf::Color::Blue) : player.SetColor(sf::Color::Magenta);
					waveManager.SetEnemiesNextPosition();
					break;
				case BeatState::NORMAL1_2:
					NormalA = { 0.650,0.500, 0.310 };
					NormalB = { -0.650, 0.500, 0.600 };
					NormalC = { 0.333, 0.278, 0.278 };
					NormalD = { 0.660, 0.000, 0.667 };
					backgroundShaderNormal.setUniform("a", NormalA);
					backgroundShaderNormal.setUniform("b", NormalB);
					backgroundShaderNormal.setUniform("c", NormalC);
					backgroundShaderNormal.setUniform("d", NormalD);
					backgroundStates.shader = &backgroundShaderNormal;
					(tickCount % 2 == 0) ? player.SetColor(sf::Color::Blue) : player.SetColor(sf::Color::Magenta);
					waveManager.SetEnemiesNextPosition();
					break;
				case BeatState::NORMAL1_3:
					NormalA = { 0.072, 0.627, 0.463 };
					NormalB = { 0.816, 0.756, 0.169 };
					NormalC = { 0.055, 0.545, 0.522 };
					NormalD = { 3.990, 4.046, 0.376 };
					backgroundShaderNormal.setUniform("a", NormalA);
					backgroundShaderNormal.setUniform("b", NormalB);
					backgroundShaderNormal.setUniform("c", NormalC);
					backgroundShaderNormal.setUniform("d", NormalD);
					backgroundStates.shader = &backgroundShaderNormal;
					(tickCount % 2 == 0) ? player.SetColor(sf::Color::Blue) : player.SetColor(sf::Color::Magenta);
					waveManager.SetEnemiesNextPosition();
					break;
				case BeatState::NORMAL2:
					backgroundStates.shader = &backgroundShaderNormal2;
					if (tickCount % 2 == 0) waveManager.SetEnemiesNextPosition();
					break;
					//CASE SLOW : ONE ON TWO
				case BeatState::SLOW:
					backgroundStates.shader = &backgroundShaderSlow;
					if (tickCount % 2 == 0) waveManager.SetEnemiesNextPosition();
					break;
					//CASE SLOW 2 : ONE ON TWO WITH S6
				case BeatState::SLOW2:
					backgroundStates.shader = &backgroundShaderSlow2;
					if (tickCount % 2 == 0) waveManager.SetEnemiesNextPosition();
					break;
					//CASE BOSS : BOSS
				case BeatState::BOSS:
					backgroundStates.shader = &backgroundShaderBoss;
					waveManager.SpawnBoss();
					break;
				case BeatState::BOSSSUBSTATE:
					backgroundStates.shader = &backgroundShaderBoss;
					if (tickCount % 2 == 0) waveManager.SetEnemiesNextPosition();
					break;
					//CASE PAUSE : NO MOVEMENT
				case BeatState::PAUSE:
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
			case BeatState::NORMAL:
				backgroundShaderNormal.setUniform("iTime", iTime);
				break;
			case BeatState::NORMAL1_2:
				backgroundShaderNormal.setUniform("iTime", iTime);
				break;
			case BeatState::NORMAL1_3:
				backgroundShaderNormal.setUniform("iTime", iTime);
				break;
			case BeatState::NORMAL2:
				backgroundShaderNormal2.setUniform("iTime", iTime);
				break;
			case BeatState::SLOW:
				backgroundShaderSlow.setUniform("iTime", iTime);
				break;
			case BeatState::SLOW2:
				backgroundShaderSlow2.setUniform("iTime", iTime);
				break;
			case BeatState::BOSS:
				backgroundShaderBoss.setUniform("iTime", iTime);
				break;
			case BeatState::BOSSSUBSTATE:
				backgroundShaderBoss.setUniform("iTime", iTime);
				break;
			case BeatState::PAUSE:
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
			window.draw(score);
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
			window.draw(backgroundRect, backgroundStates);
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