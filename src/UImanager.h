#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game;


class UImanager
{

	
public:
	UImanager();
	~UImanager();

	void mouseClicked(sf::Event event);



	// Initialize UI
	bool initPlayingUI();
	bool initdayEndUI();

	// Update and render

	void UpdateUI(float dt, const sf::Vector2f& passportPos, bool passportOpened);
	void renderPlayingUI(sf::RenderWindow& window, bool passportOpened);
	void renderDayEndUI(sf::RenderWindow& window);

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

	UImanager* UI;
	Game* game;
	PlayingState* playing;


};