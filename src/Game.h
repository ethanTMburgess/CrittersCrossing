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

//--------------
// declaring different gameStates
//-----------
enum class GameState
{
	MENU,
	PLAYING,
	DAYEND
};

// forward decleration
class UImanager;

class Game
{
public:
	Game(sf::RenderWindow& window);
	~Game();


	bool init();


	void update(float dt);
	void updateMenu(float dt);
	void updatePlaying(float dt);
	void updateDayEnd(float dt);

	void render();
	void renderMenu();
	void renderPlaying();
	void renderDayEnd();

	void mouseClicked(sf::Event event);
	bool collisionCheck(const sf::Vector2f& click, GameObject& object);
	void keyPressed(sf::Event event);
	void mousePressed(sf::Event event);
	void mouseMoved(sf::Event event);
	void mouseReleased(sf::Event event);

	int selectCritter();
	void generateDialougeDetails();
	void generatePassportDetails();
	void newDay();

	
	

private:

	//---------
	// systems
	//----------
	UImanager* uiManager;
	GameState currentState;
	sf::RenderWindow& window;
	sf::Font font;

	//-----------
	//Text items
	//------------
	sf::Text namePPtext;
	sf::Text dayPPtext;
	sf::Text reasonPPtext;

	sf::Text nameSpeechText;
	sf::Text reasonSpeechText;

	sf::Text calendarText;



	//-----------
	//sound
	//-----------
	sf::SoundBuffer buttonPressBuffer;
	sf::SoundBuffer stampPressBuffer;

	sf::Sound buttonPressSound;
	sf::Sound	stampSound;

	sf::Music BackgroundMusic;


	//-----------
	// gameObjects
	//------------
	GameObject dayEndBack;
	GameObject background;
	GameObject officeBack;
	
	GameObject passport;
	GameObject passportPhoto;

	GameObject critter;

	GameObject calendar;
	
	GameObject speechBubble;



	//---------
	// flags
	//---------
	bool critterInPosition = false;
	bool hover = false;
	bool pressed = false;
	bool passportDragged = false;
	bool passportOpened = false;
	bool critterMoveLeft = false;

	bool stampMoveLeft = false;
	bool stampMoveRight = false;
	bool stampShowing = false;

	bool isMale = false;
	bool passportValid = false;
	bool hasGeneratedDialougeDetails = false;
	bool hasGeneratedPassportDetails = false;



	//---------
	// game info
	//-----------
	int crittersSeen = 0;
	int currentCritter = 0;
	int currentDay = 0;
	int crittersPerDay = 5;
	int dayScore = 0;
	int money = 0;



	//------------
	//timers
	//------------
	float ButtonPressedTime = 0.2f;
	float stampPressedTime = 0.35f;



	//----------------
	//constatnt Values
	//----------------
	const float windowWidth = 570.0f;
	const float stampWidth = 167.0f;
	const float tabWidth = 15.0f;
	const float stampSpeed = 25.0f;
	const float stampVisible = windowWidth - stampWidth;
	const float stampHidden = windowWidth;



	//--------------
	//strings
	//-----------------
	std::string firstName;
	std::string lastName;
	std::string reason;
	std::string day;
	std::string nameDialogue;
	std::string reasonDialogue;
	std::string reasonDialoge;
	std::string newFirstName;
	std::string newLastName;
	std::string newReason;
	std::string lastFirstName;
	std::string lastLastName;
	std::string lastReason;
	std::string passportFirstName;
	std::string passportLastName;
	std::string passportReason;
	std::string passportDay;



	//-----------
	// arrays
	///-------------
	std::string firstNamesM[3] = { "Fred",
									"Eliot",
									"Logan" };

	std::string firstNamesF[2] = { "Willow",
									"Olivia" };

	std::string lastNames[5] = {    "Thistledew", 
									"Oakburrow", 
									"Bramblesnout", 
									"Nettlebrook", 
									"Fuzztail" };

	std::string reasons[5] = {  "\ntrade acorns",
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

	
	std::string daysOfWeek[7] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };


	//----------
	// dragging
	//------------
	GameObject* objectDragged = nullptr;
	sf::Vector2f dragOffset;



	
	

};

#endif // PLATFORMER_GAME_H
