#include "DayEndState.h"
#include "Game.h"
#include "UImanager.h"
#include <iostream>
#include "PlayingState.h"
#include "MenuState.h"


MenuState::MenuState(Game* game) : game(game)
{
	UI = new UImanager();
	game->currentState = GameState::MENU;
}

MenuState::~MenuState()
{
	delete UI;
}

bool MenuState::init()
{
	playText.setString("would You like to play\n Critters Crossing?");
	playText.setPosition(150, 100);
	playText.setFont(game->getFont());
	playText.setFillColor(sf::Color::White);
	playText.setCharacterSize(30);

	return true;
}

void MenuState::update(float dt)
{
	playText.setPosition(160, 100);
}

void MenuState::render(sf::RenderWindow &window)
{
	window.draw(playText);
}

