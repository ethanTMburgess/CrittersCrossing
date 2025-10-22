#pragma once
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Vector2.h"
#include <Windows.h>
#include <cmath>
#include <SFML/Audio.hpp>
#include "UImanager.h"
#include "PlayingState.h"  // Add this

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
	void mouseClicked(sf::Event event);
	void mousePressed(sf::Event event);
	void mouseMoved(sf::Event event);
	void mouseReleased(sf::Event event);
	void keyPressed(sf::Event event);

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

	sf::Music backgroundMusic;
	

private:


	

	void updateMenu(float dt);
	void updateDayEnd(float dt);
	void renderMenu();
	void renderDayEnd();

	// Systems
	UImanager* UI;
	PlayingState* playing = nullptr;


	GameObject* objectDragged = nullptr;
	sf::Vector2f dragOffset;
	bool passportDragged = false;

	GameState currentState;
	sf::RenderWindow& window;
	sf::Font font;


	

	GameObject dayEndBack;


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

	std::string reasonsShort[5] = { "Business",
									"Tourism",
									"Work",
									"Shopping",
									"Social", };

	std::string passportPhotos[5] = { "../Data/assets/crossing/critters/frog passport image.png",
									 "../Data/assets/crossing/critters/mouse passport image.png",
									 "../Data/assets/crossing/critters/duck passport image.png",
									 "../Data/assets/crossing/critters/racoon passport image.png",
									 "../Data/assets/crossing/critters/rabbit passport image.png" };

};

#endif // PLATFORMER_GAME_H