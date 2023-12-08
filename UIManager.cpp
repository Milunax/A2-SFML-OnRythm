#include "UIManager.h"

UIManager::UIManager(RefsData data)
{
	//Start Menu
	_title = CreateTextAlone(*data.window, sf::Vector2f(640.0f, 100.0f), *data.baseFont, "Epileptik Rythm", 80, sf::Text::Bold);
	_startButton = new Button(basicButton, data, sf::Vector2f(640.0f, 300.0f), "START");
	_quitButton = new Button(basicButton, data, sf::Vector2f(640.0f, 410.0f), "QUIT");

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
	_startButton->Draw(data);
	_quitButton->Draw(data);
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

Button* UIManager::GetExitButton()
{
	return _exitButton;
}
