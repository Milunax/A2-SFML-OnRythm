#include "UIManager.h"

UIManager::UIManager(RefsData data, float lowerTransparencyTime)
{
	//Start Menu
	//_title = CreateTextAlone(*data.window, sf::Vector2f(640.0f, 100.0f), *data.baseFont, "Epileptik Rythm", 80, sf::Text::Bold);
	_logoImage.loadFromFile("Assets/LogoRound.png");

	_logoTexture.loadFromFile("../Assets/LogoRound.png");
	_logoSprite.setTexture(_logoTexture);
	_logoSprite.setScale(sf::Vector2f(0.5f, 0.5f));
	_logoSprite.setPosition(sf::Vector2f(150.0f, 270.0f));
	_startButton = new Button(basicButton, data, sf::Vector2f(640.0f, 300.0f), "START");
	_quitButton = new Button(basicButton, data, sf::Vector2f(640.0f, 410.0f), "QUIT");
	//DamageTexts Fields

	_timer = 0.0f;
	_lowerTransparencyTime = lowerTransparencyTime;

	//Upgrade Menu
	_upgradeOneButton = new Button(basicButton, data, sf::Vector2f(640.0f, 300.0f), "UPGRADE");
	_upgradeTwoButton = new Button(basicButton, data, sf::Vector2f(640.0f, 410.0f), "UPGRADE");

	//End Menu
	_endTitle = CreateTextAlone(*data.window, sf::Vector2f(640.0f, 200.0f), *data.baseFont, "Game Over", 80, sf::Text::Bold);
	_exitButton = new Button(basicButton, data, sf::Vector2f(640.0f, 360.0f), "EXIT");
	_endBackground.setSize(sf::Vector2f((float)(*data.window).getSize().x, (float)(*data.window).getSize().y));
	sf::Color bgColor(0, 0, 0, 120);
	_endBackground.setFillColor(bgColor);
	_endBackground.setPosition(sf::Vector2f(0, 0));
}

void UIManager::DrawStartMenu(RefsData data)
{
	data.window->draw(_title);
	data.window->draw(_logoSprite);
	_startButton->Draw(data);
	_quitButton->Draw(data);
}

std::vector<sf::Text*>* UIManager::GetDamageTextList()
{
	return &_allDamageTexts;
}

void UIManager::Update(RefsData data)
{
	_timer += data.deltaTime;
	if (_timer >= _lowerTransparencyTime) 
	{
		UpdateAllDamageTexts(data);
		_timer = 0.0f;
	}
	EraseOldTexts();
}

void UIManager::UpdateAllDamageTexts(RefsData data)
{
	for (sf::Text* text : _allDamageTexts) 
	{
		sf::Color temp = text->getFillColor();
		temp.a = std::clamp(temp.a - 25, 0, 255);
		text->setFillColor(temp);
	}
}

void UIManager::DrawAllDamageTexts(RefsData data)
{
	for (sf::Text* text : _allDamageTexts) 
	{
		data.window->draw((*text));
	}
}

void UIManager::EraseOldTexts()
{
	std::vector<sf::Text*>::iterator it = _allDamageTexts.begin();
	while (it != _allDamageTexts.end())
	{
		if ((*it)->getFillColor().a <= 0)
		{
			delete (*it);
			it = _allDamageTexts.erase(it);
		}
		else
		{
			it++;
		}
	}
	//std::cout << _allDamageTexts.size() << std::endl;
}

void UIManager::DrawUpgradeMenu(RefsData data)
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

void UIManager::DrawEndMenu(RefsData data)
{
	data.window->draw(_endBackground);
	data.window->draw(_endTitle);
	_exitButton->Draw(data);
}

Button* UIManager::GetStartButton()
{
	return _startButton;
}

Button* UIManager::GetQuitButton()
{
	return _quitButton;
}

Button* UIManager::GetUpgradeOneButton()
{
	return _upgradeOneButton;
}

void UIManager::SetButtonOneText(WeaponData weaponData)
{
	_upgradeOneButton->SetText(weaponData.Name);
}

Button* UIManager::GetUpgradeTwoButton()
{
	return _upgradeTwoButton;
}

void UIManager::SetButtonTwoText(WeaponData weaponData)
{
	_upgradeTwoButton->SetText(weaponData.Name);
}

Button* UIManager::GetExitButton()
{
	return _exitButton;
}
