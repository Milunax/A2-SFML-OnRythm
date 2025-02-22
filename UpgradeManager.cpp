#include "UpgradeManager.h"


UpgradeManager::UpgradeManager(RefsData data)
{
	_upgradeOne = Upgrade::HEALTH;
	_upgradeTwo = Upgrade::HEALTH;

	_upgradeOneButton = new Button(basicButton, data, sf::Vector2f(640.0f, 300.0f), "UPGRADE");
	SetUpgradeButtonText(_upgradeOneButton, _upgradeOne);
	_upgradeTwoButton = new Button(basicButton, data, sf::Vector2f(640.0f, 410.0f), "UPGRADE");
	SetUpgradeButtonText(_upgradeTwoButton, _upgradeTwo);
	_player = nullptr;
}

void UpgradeManager::Init(Player* player)
{
	_player = player;
}

Upgrade UpgradeManager::GenerateUpgrade()
{
	int random = rand() % 4;
	Upgrade upgrade = (Upgrade)random;

	return upgrade;
}

void UpgradeManager::GenerateNewUpgrades() 
{
	if (_player->GetTimesWeaponUpgraded() >= 3)
	{

		do
		{
			_upgradeOne = GenerateUpgrade();
		} while (_upgradeOne == Upgrade::WEAPON);

		do
		{
			_upgradeTwo = GenerateUpgrade();
		} while (_upgradeTwo == Upgrade::WEAPON || _upgradeTwo == _upgradeOne);
	}
	else
	{
		_upgradeOne = GenerateUpgrade();

		do
		{
			_upgradeTwo = GenerateUpgrade();
		} while (_upgradeTwo == _upgradeOne);
	}

	SetUpgradeButtonText(_upgradeOneButton, _upgradeOne);
	SetUpgradeButtonText(_upgradeTwoButton, _upgradeTwo);
}

void UpgradeManager::SetUpgradeButtonText(Button* button, Upgrade upgrade)
{
	switch (upgrade)
	{
	case Upgrade::HEALTH:
		button->SetText("Health +");
		break;
	case Upgrade::ATTACK:
		button->SetText("Attack +");
		break;
	case Upgrade::ATTACKSPEED:
		button->SetText("Atk Spd +");
		break;
	case Upgrade::WEAPON:
		button->SetText("Weapon +");
		break;
	default:
		break;
	}
}

void UpgradeManager::DrawUpgradeMenu(RefsData data) 
{
	sf::RectangleShape upgradeBackground;
	upgradeBackground.setSize(sf::Vector2f((float)(*data.window).getSize().x, (float)(*data.window).getSize().y));
	sf::Color bgColor(0, 0, 0, 120);
	upgradeBackground.setFillColor(bgColor);
	upgradeBackground.setPosition(sf::Vector2f(0, 0));
	sf::Text upgradeTitle = CreateTextAlone(*data.window, sf::Vector2f(640.0f, 100.0f), *data.baseFont, "Level Up !", 80, sf::Text::Bold);

	(*data.window).draw(upgradeBackground);
	(*data.window).draw(upgradeTitle);

	_upgradeOneButton->Draw(data);
	_upgradeTwoButton->Draw(data);
}

Upgrade UpgradeManager::GetUpgradeOne() 
{
	return _upgradeOne;
}

Upgrade UpgradeManager::GetUpgradeTwo()
{
	return _upgradeTwo;
}

Button* UpgradeManager::GetUpgradeOneButton()
{
	return _upgradeOneButton;
}
Button* UpgradeManager::GetUpgradeTwoButton()
{
	return _upgradeTwoButton;
}