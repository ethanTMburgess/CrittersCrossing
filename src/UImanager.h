#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class UImanager
{
public:
	UImanager();

	// Initialize UI
	bool initPlayingUI();

	// Update and render

	void UpdateUI(float dt, const sf::Vector2f& passportPos, bool passportOpened);
	void renderUI(sf::RenderWindow& window, bool passportOpened);

	//sounds
	sf::SoundBuffer buttonPressBuffer;
	sf::SoundBuffer stampPressBuffer;
	sf::Sound buttonPressSound;
	sf::Sound stampSound;

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
	
	GameObject nextDayButton;
	GameObject calendar;
	GameObject speechBubble;
	GameObject officeBack;


private:
	// UI constants
	const float windowWidth = 570.0f;
	const float stampWidth = 167.0f;

	


};