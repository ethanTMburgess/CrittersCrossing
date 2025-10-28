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
	playButton.getImageFromPath(".. /Data/assets/crossing/UI/yes button.png");
	playButton.setPosition(200, 200);

	quitButton.getImageFromPath(".. /Data/assets/crossing/UI/no button.png");
	quitButton.setPosition(playButton.sprite.getPosition().x + 200, playButton.sprite.getPosition().y);

	playText.setString("would You like to play\nCritters Crossing?");
	playText.setPosition(200, 100);
	playText.setFont(game->getFont());
	playText.setFillColor(sf::Color::White);
	playText.setCharacterSize(30);
}

void MenuState::update(float dt)
{

}

void MenuState::render()
{

}

