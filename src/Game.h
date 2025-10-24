#pragma once
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include "GameObject.h"


class GameObject;
class UImanager;
class PlayingState;
class DayEndState;

enum class GameState
{
	MENU,
	PLAYING,
	DAYEND
};

class Game
{
public:
	Game(sf::RenderWindow& window);
	~Game();

	bool init();
	void update(float dt);
	void render();

	// Input handling
	
	void mousePressed(sf::Event event);
	void mouseMoved(sf::Event event);
	void mouseReleased(sf::Event event);
	void keyPressed(sf::Event event);

	bool collisionCheck(const sf::Vector2f& click, GameObject& object);

	// Getters
	sf::RenderWindow& getWindow() { return window; }
	sf::Font& getFont() { return font; }
	UImanager* getUI() { return UI; }
	int getCurrentDay() const { return currentDay; }
	int getCrittersPerDay() const { return crittersPerDay; }
	std::string* getDaysOfWeek() { return daysOfWeek; }
	std::string* getFirstNamesM() { return firstNamesM; }
	std::string* getFirstNamesF() { return firstNamesF; }
	std::string* getLastNames() { return lastNames; }
	
	std::string* getReasons() { return reasons; }
	std::string* getReasonsShort() { return reasonsShort; }

	std::string* getPassportPhotos() { return passportPhotos; }

	void setState(GameState newState) { currentState = newState; }
	void newDay();

	int getDayScore() { return dayScore; }
	void setDayScore(int score) { dayScore = score; }
	PlayingState* getPlayingState() { return playing; }

	sf::Color getTextColor()const { return textColor; }

	//
	// static const sf::Color TEXT_COLOR;
	//

	sf::Music backgroundMusic;
	

private:

	sf::Color textColor = sf::Color(55, 55, 55);
	

	void updateMenu(float dt);
	void updateDayEnd(float dt);
	void renderMenu();
	void renderDayEnd();

	// Systems
	UImanager* UI = nullptr;
	PlayingState* playing = nullptr;
	DayEndState* dayEnd = nullptr;


	GameObject* objectDragged = nullptr;
	sf::Vector2f dragOffset;
	bool passportDragged = false;

	GameState currentState;
	sf::RenderWindow& window;
	sf::Font font;


	

	


	int currentDay = 0;
	const int crittersPerDay = 5;
	int money = 0;
	int dayScore = 0;

	// Shared arrays
	std::string daysOfWeek[7] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

	std::string firstNamesM[3] = { "Fred",
									"Eliot",
									"Logan" };

	std::string firstNamesF[2] = { "Willow",
									"Olivia" };

	std::string lastNames[5] = { "Thistledew",
									"Oakburrow",
									"Bramblesnout",
									"Nettlebrook",
									"Fuzztail" };

	std::string reasons[5] = { "\ntrade acorns",
								"\nvisit the forest fair",
								"fix \na broken cart wheel",
								"\nvisit the shops",
								"\nmeet somebody by the old well" };

	std::string reasonsShort[5] = { "trading",
									"forrest fair",
									"Handy work",
									"Shopping",
									"social visit", };

	std::string passportPhotos[5] = { "../Data/assets/crossing/critters/frog passport image.png",
									 "../Data/assets/crossing/critters/mouse passport image.png",
									 "../Data/assets/crossing/critters/duck passport image.png",
									 "../Data/assets/crossing/critters/racoon passport image.png",
									 "../Data/assets/crossing/critters/rabbit passport image.png" };

};

#endif // PLATFORMER_GAME_H