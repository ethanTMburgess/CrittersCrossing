#include "DayEndState.h"
#include "Game.h"
#include "UImanager.h"
#include <iostream>

DayEndState::DayEndState(Game* game) : game(game)
{

	UI = new UImanager();
	game->currentState = GameState::DAYEND;
	
}

DayEndState::~DayEndState()
{
	delete UI;
}

bool DayEndState::init()
{
	dayScore = game->getDayScore();
	

	sf::Font& font = game->getFont();
	font.setSmooth(false);

	

	dayScoreText.setFont(font);
	dayScoreText.setString(std::to_string(dayScore));
	dayScoreText.setCharacterSize(32);
	dayScoreText.setFillColor(sf::Color (55, 55, 55));
	dayScoreText.setPosition(97, 65);
	dayScoreText.setFillColor(sf::Color::Black);
	
	moneyText.setFont(font);
	moneyText.setString(std::to_string(game->money));
	moneyText.setCharacterSize(32);
	moneyText.setFillColor(sf::Color(55, 55, 55));
	moneyText.setPosition(97, 146);
	moneyText.setFillColor(sf::Color::Black);
	


	dayEndBack.getImageFromPath("../data/assets/crossing/UI/day end screen.png");
	dayEndBack.setPosition(0, 0);

	
	return true;
}

void DayEndState::update(float dt)
{
	
}

void DayEndState::render(sf::RenderWindow& window)
{

	
	dayEndBack.render(window);
	
	UI->nextDayButton.render(window);

	window.draw(moneyText);
	window.draw(dayScoreText);

}