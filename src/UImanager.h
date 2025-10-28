#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game;
class PlayingState;

class UImanager
{

	
public:
	UImanager();
	

	void mouseClicked(sf::RenderWindow& window, sf::Event event);



	// Initialize UI
	bool initPlayingUI();
	bool initdayEndUI();
	bool initMenuUI();

	// Update and render

	void UpdateUI(float dt, const sf::Vector2f& passportPos, bool passportOpened);
	void renderPlayingUI(sf::RenderWindow& window, bool passportOpened);
	void renderDayEndUI(sf::RenderWindow& window);
	void renderMenuUI(sf::RenderWindow& window);

	void setgame(Game* gamePtr) { game = gamePtr; }
	void setPlayingState(PlayingState* playingState) { playing = playingState; }

	//sounds
	sf::SoundBuffer buttonPressBuffer;
	sf::SoundBuffer stampPressBuffer;
	sf::Sound buttonPressSound;
	sf::Sound stampSound;




	// getters and setters for these variables, then move to private
	// UI state
	bool yesButtonDown = false;
	bool noButtonDown = false;
	bool stampDown = false;
	bool stampShowing = false;
	bool stampMoveRight = false;
	bool stampMoveLeft = false;
	bool yesButtonPressed = false;
	bool noButtonPressed = false;
	bool nextButtonPressed = false;
	bool stampPressed = false;
	bool yesStampApplied = false;
	bool noStampApplied = false;
	const float stampSpeed = 25.0f;


	bool passportValid = false;

	float ButtonTimer = 0.0f;

	const float stampVisible = 407;//windowWidth - stampWidth;
	const float stampHidden = 570;// windowWidth;



	// UI objects
	GameObject yesButton;
	GameObject noButton;
	GameObject nextButton;
	GameObject stamp;
	GameObject stampTab;
	GameObject stampShadow;

	GameObject playButton;
	GameObject quitButton;



	
	
	
	GameObject calendar;
	GameObject speechBubble;
	GameObject officeBack;

	GameObject nextDayButton;
	GameObject dayEndBackground;

private:
	// UI constants
	const float windowWidth = 570.0f;
	const float stampWidth = 167.0f;

	int dayScore;

	
	Game* game;
	PlayingState* playing;


};