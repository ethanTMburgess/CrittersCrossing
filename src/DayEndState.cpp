#include "DayEndState.h"
#include "Game.h"
#include "UImanager.h"
#include <iostream>

DayEndState::DayEndState(Game* game) : game(game)
{

	UI = new UImanager();

	
}

DayEndState::~DayEndState()
{
	delete UI;
}

bool DayEndState::init()
{
	dayScore = game->getDayScore();

	sf::Font& font = game->getFont();


	dayEndBack.getImageFromPath("../data/assets/crossing/UI/day end screen.png");
	dayEndBack.setPosition(0, 0);

	
	return true;
}

void DayEndState::update(float dt)
{
	
}

void DayEndState::render(sf::RenderWindow& window)
{
	UI->nextDayButton.render(window);
}