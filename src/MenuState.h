#pragma once
#include "UImanager.h"
#include "Game.h"


class Game;
class UImanager;


class MenuState {
private:
	

	Game* game;
	UImanager* UI;

	sf::Text playText;

public:
	MenuState(Game* game);
	~MenuState();


	bool init();
	void update(float dt);
	void render(sf::RenderWindow &window);
};
