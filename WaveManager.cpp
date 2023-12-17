#include "WaveManager.h"
#include "GameManager.h"

WaveManager::WaveManager(float timer, float spawnTime, int numberOfEnemiesToSpawn, int maxEnemyCount, float factorAugment)
{
	_timer = timer;
	_spawnTime = spawnTime;
	_numberOfEnemiesToSpawn = numberOfEnemiesToSpawn;
	_maxEnemyCount = maxEnemyCount;

	_enemyMoveMultiplier = 1.0f;

	_enemyScaleFactor = 1.0f;
	_factorAugment = factorAugment;

	_gameManager = nullptr;
	_player = nullptr;
	_particleSystem = nullptr;
	_uiManager = nullptr;
}

void WaveManager::Init(sf::RenderWindow& window,GameManager* gameManager, Player* player, ParticleSystem* particleSystem, UIManager* uiManager)
{
	std::vector<sf::Vector2f> positions{
		sf::Vector2f(-50, -50),
		sf::Vector2f(window.getSize().x / 2, -50),
		sf::Vector2f(window.getSize().x + 50, -50),
		sf::Vector2f(window.getSize().x + 50, window.getSize().y / 2),
		sf::Vector2f(window.getSize().x + 50, window.getSize().y + 50),
		sf::Vector2f(window.getSize().x / 2, window.getSize().y + 50),
		sf::Vector2f(-50, window.getSize().y + 50),
		sf::Vector2f(-50, window.getSize().y / 2)
	};

	for (sf::Vector2f position : positions) {
		_spawners.push_back(new EnemySpawner(position));
	}

	_gameManager = gameManager;
	_player = player;
	_particleSystem = particleSystem;
	_uiManager = uiManager;
}

void WaveManager::Update(RefsData data) 
{
	UpdateAllEnemies(data.deltaTime);
	CheckCollisionAllEnemies();
	_timer += data.deltaTime;
	if (_timer > _spawnTime) 
	{
		SpawnWave();
		_timer = 0;
	}
	ShowEnemiesDamageTaken(data);
	EraseDeadEnemies();
}

void WaveManager::SpawnWave()
{
	int numberToSpawn = _numberOfEnemiesToSpawn;
	for (int i = 0; i < _spawners.size(); i++)
	{
		if (_enemyList.size() < _maxEnemyCount) 
		{
			if (numberToSpawn < _spawners.size() - (i + 1))
			{
				int random = rand() % 2;
				if (numberToSpawn > 0 && random == 1) {
					Enemy* enemy = _spawners[i]->InstantiateEnemy(normalEnemy, _spawners[i]->GetPosition(), _player);
					enemy->ScaleStats(_enemyScaleFactor);
					_enemyList.push_back(enemy);
					numberToSpawn--;
				}
			}
			else
			{
				Enemy* enemy = _spawners[i]->InstantiateEnemy(normalEnemy, _spawners[i]->GetPosition(), _player);
				enemy->ScaleStats(_enemyScaleFactor);
				_enemyList.push_back(enemy);
				numberToSpawn--;
			}
		}
		
		if (_enemyList.size() >= _maxEnemyCount) return;
		if (numberToSpawn <= 0) return;
	}
}

void WaveManager::SpawnBoss() 
{
	int random = rand() % _spawners.size();
	Enemy* boss = _spawners[random]->InstantiateEnemy(bossEnemy, _spawners[random]->GetPosition(), _player);
	boss->ScaleStats(_enemyScaleFactor);
	_enemyList.push_back(boss);
}

void WaveManager::SetMoveMultiplier(float value)
{
	_enemyMoveMultiplier = value;
}

void WaveManager::AugmentScaleFactor()
{
	_enemyScaleFactor *= _factorAugment;
}

void WaveManager::SetEnemiesNextPosition() 
{
	for (Enemy* enemy : _enemyList)
	{
		enemy->SetNextPosition(_enemyMoveMultiplier);
	}
}

void WaveManager::UpdateAllEnemies(float deltaTime)
{
	for (Enemy* enemy : _enemyList)
	{
		enemy->Update(deltaTime, _enemyMoveMultiplier);
	}
}

void WaveManager::CheckCollisionAllEnemies() 
{
	CircleCollider playerCol = _player->GetCollider();

	for (Enemy* enemy : _enemyList) 
	{
		CircleCollider enemyCol = enemy->GetCollider();
		if (AreCircleCollidersOverlapping(enemyCol, playerCol))
		{
			enemy->Attack();
			ClampCircleOutsideCircle(enemyCol, playerCol);
			enemy->SetPosition(enemyCol.Origin);
		}
	}
}

void WaveManager::ShowEnemiesDamageTaken(RefsData data)
{
	for (Enemy* enemy : _enemyList) 
	{
		if (enemy->HasTakenDamage == true) 
		{
			sf::Text* text = CreateTextAtPosition((*data.window), (enemy)->GetPosition(), (*data.baseFont), IntStringConcatenate(enemy->GetDamageTaken(), ""), 24);
			_uiManager->GetDamageTextList()->push_back(text);
			enemy->HasTakenDamage = false;
		}
	}
}

void WaveManager::EraseDeadEnemies() 
{
	std::vector<Enemy*>::iterator it = _enemyList.begin();
	while (it != _enemyList.end()) 
	{
		if (!(*it)->IsAlive) 
		{
			_player->AddExperience((*it)->GetExperienceDropped());
			_gameManager->AddScore((*it)->GetScore());
			_particleSystem->Explosion((*it)->GetPosition());
			delete (*it);
			it = _enemyList.erase(it);
		}
		else 
		{
			it++;
		}
	}
}

void WaveManager::DrawAllEnemies(sf::RenderWindow& window)
{
	for (Enemy* enemy : _enemyList) 
	{
		enemy->Draw(window);
	}

}

std::vector<Enemy*>* WaveManager::GetEnemyList()
{
	return &_enemyList;
}
