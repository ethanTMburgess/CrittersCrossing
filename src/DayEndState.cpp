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

	if (&font == nullptr)
	{
		std::cout << "font is null in day end" << std::endl;
	}

	dayScoreText.setFont(font);
	dayScoreText.setString(std::to_string(dayScore));
	dayScoreText.setCharacterSize(20);
	dayScoreText.setFillColor(sf::Color (55, 55, 55));
	dayScoreText.setPosition(97, 80);
	dayScoreText.setFillColor(sf::Color::Red);
	
	


	dayEndBack.getImageFromPath("../data/assets/crossing/UI/day end screen.png");
	dayEndBack.setPosition(0, 0);

	
	return true;
}

void DayEndState::update(float dt)
{
	
}

void DayEndState::render(sf::RenderWindow& window)
{
	if (dayScoreText.getString().isEmpty())
	{
		std::cout << "DAY SCORE IS EMPTY" << std::endl;
	}
	
	dayEndBack.render(window);
	
	UI->nextDayButton.render(window);

	window.draw(dayScoreText);

}