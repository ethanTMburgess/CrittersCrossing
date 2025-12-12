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
class MenuState;

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
	UImanager* getUI() { return UI.get(); }
	int getCurrentDay() const { return currentDay; }
	int getCrittersPerDay() const { return crittersPerDay; }

	

	

	// std::string* getDaysOfWeek() { return daysOfWeek; }
	//std::string* getFirstNamesM() { return firstNamesM; }
	//std::string* getLastNames() { return lastNames; }
	//std::string* getFirstNamesF() { return firstNamesF; }

	const std::vector < std::string>& getFirstNamesMvector() const { return vFirstNamesM; }
	const std::vector < std::string>& getFirstNamesFvector() const { return vFirstNamesF; }
	const std::vector <std::string>& getLastNamesVector() const { return vLastNames; }
	const std::vector <std::string>& getReasonsVector() const { return reasons; }
	const std::vector <std::string>& getReasonsShortVector() const { return reasonsShort; }
	const std::vector <std::string>& getPassportPhotosVector() const { return passportPhotos; }

	const std::vector <std::string>& getDaysOfWeekVector() const { return daysOfWeek; }


	// std::string* getReasons() { return reasons; }

	// std::string* getReasonsShort() { return reasonsShort; }

	// std::string* getPassportPhotos() { return passportPhotos; }

	GameState currentState;
	void setState(GameState newState) { currentState = newState; }
	void newDay();

	int getDayScore() { return dayScore; }
	
	void setCurrentDay(int day) { currentDay = day; }

	void setDayScore(int score) { dayScore = score; }
	PlayingState* getPlayingState() { return playing.get(); }

	sf::Color getTextColor()const { return textColor; }

	//
	// static const sf::Color TEXT_COLOR;
	//

	sf::Music backgroundMusic;

	std::vector <std::string> daysOfWeek  = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
	int currentDay = 0;

	int money = 0;


private:

	sf::Color textColor = sf::Color(55, 55, 55);


	void updateMenu(float dt);

	void renderMenu();
	void renderDayEnd();

	// Systems
	// 
	//UImanager* UI;
	//PlayingState* playing;
	//DayEndState* dayEnd;
	//MenuState* menu;

	std::unique_ptr<UImanager> UI;
	std::unique_ptr < PlayingState> playing;
	std::unique_ptr < DayEndState> dayEnd;
	std::unique_ptr < MenuState> menu;

	GameObject* objectDragged = nullptr;
	sf::Vector2f dragOffset;
	bool passportDragged = false;


	sf::RenderWindow& window;
	sf::Font font;





	


	const int crittersPerDay = 5;

	int dayScore = 0;
	

	// Shared arrays

	std::vector<std::string> vFirstNamesM = { "Fred",
									"Eliot",
									"Logan" };

	

	 std::vector<std::string> vFirstNamesF = { "Willow", "Olivia" };
	
	

	std::vector<std::string> vLastNames = { "Thistledew",
									"Oakburrow",
									"Bramblesnout",
									"Nettlebrook",
									"Fuzztail" };


	


	std:: vector <std::string> reasons = { "\ntrade acorns",

								"\nvisit the forest fair",

								"fix \na broken cart wheel",

								"\nvisit the shops",

								"\nmeet somebody by the old well" };


	

	std::vector <std::string> reasonsShort = { "trading",
									"Fair",

									"Handy work",

									"Shopping",

									"social visit", };

	std::vector <std::string> passportPhotos = { "../Data/assets/crossing/critters/frog passport image.png",
									 "../Data/assets/crossing/critters/mouse passport image.png",
									 "../Data/assets/crossing/critters/duck passport image.png",
									 "../Data/assets/crossing/critters/racoon passport image.png",
									 "../Data/assets/crossing/critters/rabbit passport image.png" };

	
};

#endif // PLATFORMER_GAME_H