#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameObject.h"
// Forward declarations for all classes you use
class Game;
class UImanager;
class PlayingState;

class DayEndState
{
public:
	DayEndState(Game* game);
	~DayEndState();

	bool init();
	void update(float dt);
	void render(sf::RenderWindow& window);

private:
	Game* game;
	UImanager* UI;
	PlayingState* playing;

	int dayScore = 0;

	GameObject dayEndBack;

	sf::Text dayScoreText;
	sf::Text moneyText;
};