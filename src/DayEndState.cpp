#include "DayEndState.h"
#include "Game.h"
#include "UImanager.h"
#include <iostream>

DayEndState::DayEndState(Game* game) : game(game)
{
	// UI = game->getUI();
	UI = new UImanager();

	dayScore = game->getDayScore();
}

DayEndState::~DayEndState()
{
	delete UI;
}

bool DayEndState::init()
{

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