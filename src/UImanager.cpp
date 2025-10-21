#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <Windows.h>
#include <cmath>

#include "Game.h"
#include "GameObject.h"
#include "Vector2.h"
#include "UImanager.h"
#include "PlayingState.h"
#include "MenuState.h"
#include "DayEndState.h"
#include "GameStateManager.h"






void Game::mouseClicked(sf::Event event)
{
	//get the click position
	sf::Vector2i pixelClick{ event.mouseButton.x, event.mouseButton.y };
	sf::Vector2f worldClick = window.mapPixelToCoords(pixelClick);

	if (collisionCheck(worldClick, uiManager->yesButton))
	{

		std::cout << "yes button clicked\n";
		uiManager->yesButton.getImageFromPath("../Data/assets/crossing/UI/yes button pressed.png");

		officeBack.getImageFromPath("../Data/assets/crossing/UI/green office back.png");

		buttonPressSound.play();

		uiManager->yesButtonDown = true;
		uiManager->ButtonTimer = 0.0f;

		uiManager->yesButtonPressed = true;

		uiManager->noButtonPressed = false;


	}

	if (collisionCheck(worldClick, uiManager->nextDayButton))
	{

	}

	if (collisionCheck(worldClick, uiManager->noButton))
	{
		std::cout << "no button clicked\n";
		uiManager->noButton.getImageFromPath("../Data/assets/crossing/UI/no button pressed.png");

		officeBack.getImageFromPath("../Data/assets/crossing/UI/red office back.png");

		buttonPressSound.play();

		uiManager->noButtonDown = true;
		uiManager->ButtonTimer = 0.0f;

		uiManager->noButtonPressed = true;
		uiManager->yesButtonPressed = false;
	}


	// next button should only work if a descision has been made by the player

	sf::Vector2f passportPos = passport.sprite.getPosition();
	if (collisionCheck(worldClick, uiManager->nextButton) && (uiManager->yesButtonPressed || uiManager->noButtonPressed) && uiManager->stampPressed && passportPos.x < 139)
	{

		std::cout << "next button clicked\n";
		uiManager->nextButton.getImageFromPath("../Data/assets/crossing/UI/next button pressed.png");

		officeBack.getImageFromPath("../Data/assets/crossing/UI/grey office back.png");
		uiManager->nextButtonPressed = true;
		uiManager->ButtonTimer = 0.0f;

		if (uiManager->noButtonPressed && passportValid)
		{
			std::cout << "passport was valid but denied\n";
			dayScore = dayScore - 1;
		}

		else if (uiManager->noButtonPressed && !passportValid)
		{
			std::cout << "passport was invalid and denied\n";
			dayScore = dayScore + 1;
		}

		else if (uiManager->yesButtonPressed && !passportValid)
		{
			std::cout << "passport was invalid but allowed\n";
			dayScore = dayScore - 1;
		}

		else if (uiManager->yesButtonPressed && passportValid)
		{
			std::cout << "passport was valid and allowed\n";
			dayScore = dayScore + 1;
		}



		buttonPressSound.play();

		// make critter move left off screen
		critterMoveLeft = true;

		uiManager->yesButtonPressed = false;
		uiManager->noButtonPressed = false;
		uiManager->stampPressed = false;

		uiManager->yesStampApplied = false;
		uiManager->noStampApplied = false;

		hasGeneratedDialougeDetails = false;
		hasGeneratedPassportDetails = false;

		critterInPosition = false;

		crittersSeen = crittersSeen + 1;


	}
	else if (collisionCheck(worldClick, uiManager->nextButton))
	{
		std::cout << "select [yes / no]\n";
	}

	if (collisionCheck(worldClick, passport))
	{
		std::cout << "passport clicked\n";
		hover = true;

	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////
	if (collisionCheck(worldClick, uiManager->stampTab) && stampShowing == false)
	{
		std::cout << "stamp tab clicked\n";
		stampMoveLeft = true;

		stampMoveRight = false;

		stampShowing = true;


	}

	else if (collisionCheck(worldClick, uiManager->stampTab) && stampShowing == true)
	{
		std::cout << "stamp tab clicked\n";

		stampMoveLeft = false;

		stampMoveRight = true;

		stampShowing = false;



	}

	if (collisionCheck(worldClick, uiManager->stamp) && stampShowing == true && (uiManager->yesButtonPressed || uiManager->noButtonPressed))
	{
		uiManager->stampDown = true;
		std::cout << "stamp clicked\n";
		uiManager->stamp.getImageFromPath("../Data/assets/crossing/UI/stamp pressed.png");
		uiManager->ButtonTimer = 0.0f;

		stampSound.play();
	}


}