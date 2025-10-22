#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <Windows.h>
#include <cmath>


#include "GameObject.h"
#include "Vector2.h"
#include "UImanager.h"
#include "PlayingState.h"
#include "GameStateManager.h"


UImanager::UImanager()
{
	
	passportValid = false;
}



bool UImanager::initPlayingUI()
{

	stampShowing = false;
	stampMoveLeft = false;
	stampMoveRight = false;



	stamp.getImageFromPath("../Data/assets/crossing/UI/stamp.png");
	stamp.setPosition(570, 90);

	stampTab.getImageFromPath("../Data/assets/crossing/UI/stamp tab.png");
	stampTab.setPosition(stamp.sprite.getPosition().x - 15, stamp.sprite.getPosition().y + 32);

	stampShadow.getImageFromPath("../Data/assets/crossing/UI/stamp shadow.png");
	

	yesButton.getImageFromPath("../Data/assets/crossing/UI/yes button.png");
	yesButton.setPosition(290 - 5, 20);

	noButton.getImageFromPath("../Data/assets/crossing/UI/no button.png");
	noButton.setPosition(390 - 15, 20);

	nextButton.getImageFromPath("../Data/assets/crossing/UI/next button.png");
	nextButton.setPosition(490 - 10, 20);

	calendar.getImageFromPath("../Data/assets/crossing/UI/calendar.png");
	calendar.setPosition(283, 79);

	officeBack.getImageFromPath("../Data/assets/crossing/UI/grey office back.png");
	officeBack.setPosition(1, 1);





	return true;
}



void Game::mouseClicked(sf::Event event)
{
	//get the click position
	sf::Vector2i pixelClick{ event.mouseButton.x, event.mouseButton.y };
	sf::Vector2f worldClick = window.mapPixelToCoords(pixelClick);

	if (playing->collisionCheck(worldClick, UI->yesButton))
	{

		std::cout << "yes button clicked\n";
		UI->yesButton.getImageFromPath("../Data/assets/crossing/UI/yes button pressed.png");

		UI->officeBack.getImageFromPath("../Data/assets/crossing/UI/green office back.png");

		playing->buttonPressSound.play();

		UI->yesButtonDown = true;
		UI->ButtonTimer = 0.0f;

		UI->yesButtonPressed = true;

		UI->noButtonPressed = false;


	}

	if (playing->collisionCheck(worldClick, UI->nextDayButton))
	{

	}

	if (playing->collisionCheck(worldClick, UI->noButton))
	{
		std::cout << "no button clicked\n";
		UI->noButton.getImageFromPath("../Data/assets/crossing/UI/no button pressed.png");

		UI->officeBack.getImageFromPath("../Data/assets/crossing/UI/red office back.png");

		playing->buttonPressSound.play();

		UI->noButtonDown = true;
		UI->ButtonTimer = 0.0f;

		UI->noButtonPressed = true;
		UI->yesButtonPressed = false;
	}


	// next button should only work if a descision has been made by the player

	sf::Vector2f passportPos = playing->passport.sprite.getPosition();
	if (playing->collisionCheck(worldClick, UI->nextButton) && (UI->yesButtonPressed || UI->noButtonPressed) && UI->stampPressed && passportPos.x < 139)
	{

		std::cout << "next button clicked\n";
		UI->nextButton.getImageFromPath("../Data/assets/crossing/UI/next button pressed.png");


		UI->officeBack.getImageFromPath("../Data/assets/crossing/UI/grey office back.png");
		UI->nextButtonPressed = true;
		UI->ButtonTimer = 0.0f;

		if (UI->noButtonPressed && playing->passportValid)
		{
			std::cout << "passport was valid but denied\n";
			dayScore = dayScore - 1;
		}

		else if (UI->noButtonPressed && !playing->passportValid)
		{
			std::cout << "passport was invalid and denied\n";
			dayScore = dayScore + 1;
		}

		else if (UI->yesButtonPressed && !playing->passportValid)
		{
			std::cout << "passport was invalid but allowed\n";
			dayScore = dayScore - 1;
		}

		else if (UI->yesButtonPressed && playing->passportValid)
		{
			std::cout << "passport was valid and allowed\n";
			dayScore = dayScore + 1;
		}



		playing->buttonPressSound.play();

		// make critter move left off screen
		playing->critterMoveLeft = true;

		UI->yesButtonPressed = false;
		UI->noButtonPressed = false;
		UI->stampPressed = false;

		UI->yesStampApplied = false;
		UI->noStampApplied = false;

		playing->hasGeneratedDialougeDetails = false;
		playing->hasGeneratedPassportDetails = false;

		playing->critterInPosition = false;

		playing->crittersSeen = playing->crittersSeen + 1;


	}
	else if (playing->collisionCheck(worldClick, UI->nextButton))
	{
		std::cout << "select [yes / no]\n";
	}

	if (playing->collisionCheck(worldClick, playing->passport))
	{
		std::cout << "passport clicked\n";
		playing->hover = true;

	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////
	if (playing->collisionCheck(worldClick, UI->stampTab) && UI->stampShowing == false)
	{
		std::cout << "stamp tab clicked\n";
		UI->stampMoveLeft = true;

		UI->stampMoveRight = false;

		UI->stampShowing = true;


	}

	else if (playing->collisionCheck(worldClick, UI->stampTab) && UI->stampShowing == true)
	{
		std::cout << "stamp tab clicked\n";

		UI->stampMoveLeft = false;

		UI->stampMoveRight = true;

		UI->stampShowing = false;



	}

	if (playing->collisionCheck(worldClick, UI->stamp) && UI->stampShowing == true && (UI->yesButtonPressed || UI->noButtonPressed))
	{
		UI->stampDown = true;
		std::cout << "stamp clicked\n";
		UI->stamp.getImageFromPath("../Data/assets/crossing/UI/stamp pressed.png");
		UI->ButtonTimer = 0.0f;

		playing->stampSound.play();
	}


}

void UImanager::UpdateUI(float dt, const sf::Vector2f& passportPos, bool passportOpened)
{

	



	stampTab.setPosition(stamp.sprite.getPosition().x - 15, stamp.sprite.getPosition().y + 32);
	stampShadow.setPosition(stamp.sprite.getPosition().x, stamp.sprite.getPosition().y + 70);

	if (stampMoveLeft)
	{
		stamp.setVector(-1, 0);
		stamp.setSpeed(stampSpeed);
		stamp.move(stamp.getVector()->x * stamp.getSpeed(), stamp.getVector()->y * stamp.getSpeed());

		if (stamp.sprite.getPosition().x <= stampVisible)
		{
			stamp.setPosition(stampVisible, 90);
			stampMoveLeft = false;
			stampShowing = true;
		}
	}

	if (stampMoveRight)
	{
		stamp.setVector(1, 0);
		stamp.setSpeed(stampSpeed);
		stamp.move(stamp.getVector()->x * stamp.getSpeed(), stamp.getVector()->y * stamp.getSpeed());

		if (stamp.sprite.getPosition().x >= stampHidden)
		{
			stamp.setPosition(stampHidden, 90);
			stampMoveLeft = false;
			stampShowing = false;
		}

	}
}

void UImanager::renderUI(sf::RenderWindow& window, bool passportOpened)
{
	

	yesButton.render(window);
	noButton.render(window);
	nextButton.render(window);

	// Render stamp system
	stampShadow.render(window);
	stamp.render(window);
	stampTab.render(window);

	
}
