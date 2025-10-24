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



UImanager::UImanager()
{
	UI = new UImanager();
	//playing = new PlayingState(this);
	passportValid = false;
	dayScore = game->getDayScore();
	
}
UImanager::~UImanager()
{
	delete UI;
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

bool UImanager::initdayEndUI()
{


	dayEndBackground.getImageFromPath("../Data/assets/crossing/UI/day end screen.png");
	dayEndBackground.setPosition(0, 0);

	nextDayButton.getImageFromPath("../Data/assets/crossing/UI/power button.png");
	nextDayButton.setPosition(416, 143);
	return true;
}



void UImanager::mouseClicked(sf::Event event)
{
	//get the click position
	sf::Vector2i pixelClick{ event.mouseButton.x, event.mouseButton.y };
	sf::Vector2f worldClick = window.mapPixelToCoords(pixelClick);

	if (game->collisionCheck(worldClick, yesButton))
	{

		std::cout << "yes button clicked\n";
		yesButton.getImageFromPath("../Data/assets/crossing/UI/yes button pressed.png");

		officeBack.getImageFromPath("../Data/assets/crossing/UI/green office back.png");

		UI->buttonPressSound.play();

		UI->yesButtonDown = true;
		UI->ButtonTimer = 0.0f;

		UI->yesButtonPressed = true;

		UI->noButtonPressed = false;


	}

	if (game->collisionCheck(worldClick, nextDayButton))
	{

	}

	if (game->collisionCheck(worldClick, noButton))
	{
		std::cout << "no button clicked\n";
		noButton.getImageFromPath("../Data/assets/crossing/UI/no button pressed.png");

		officeBack.getImageFromPath("../Data/assets/crossing/UI/red office back.png");

		UI->buttonPressSound.play();

		noButtonDown = true;
		ButtonTimer = 0.0f;

		noButtonPressed = true;
		yesButtonPressed = false;
	}


	// next button should only work if a descision has been made by the player

	sf::Vector2f passportPos = playing-> passport.sprite.getPosition();
	if (game->collisionCheck(worldClick, nextButton) && (yesButtonPressed || noButtonPressed) && stampPressed && passportPos.x < 139)
	{

		std::cout << "next button clicked\n";
		nextButton.getImageFromPath("../Data/assets/crossing/UI/next button pressed.png");


		officeBack.getImageFromPath("../Data/assets/crossing/UI/grey office back.png");
		nextButtonPressed = true;
		ButtonTimer = 0.0f;

		if (noButtonPressed && playing->passportValid)
		{
			std::cout << "passport was valid but denied\n";
			 dayScore = dayScore - 1;
		}

		else if (noButtonPressed && !playing->passportValid)
		{
			std::cout << "passport was invalid and denied\n";
			dayScore = UI->dayScore + 1;
		}

		else if (yesButtonPressed && !playing->passportValid)
		{
			std::cout << "passport was invalid but allowed\n";
			UI->dayScore = UI->dayScore - 1;
		}

		else if (UI->yesButtonPressed && playing->passportValid)
		{
			std::cout << "passport was valid and allowed\n";
			UI-> dayScore = dayScore + 1;
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
	else if (game->collisionCheck(worldClick, UI->nextButton))
	{
		std::cout << "select [yes / no]\n";
	}

	if (game->collisionCheck(worldClick, playing->passport))
	{
		std::cout << "passport clicked\n";
		playing->hover = true;

	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////
	if (game->collisionCheck(worldClick, UI->stampTab) && UI->stampShowing == false)
	{
		std::cout << "stamp tab clicked\n";
		UI->stampMoveLeft = true;

		UI->stampMoveRight = false;

		UI->stampShowing = true;


	}

	else if (game->collisionCheck(worldClick, UI->stampTab) && UI->stampShowing == true)
	{
		std::cout << "stamp tab clicked\n";

		UI->stampMoveLeft = false;

		UI->stampMoveRight = true;

		UI->stampShowing = false;



	}

	if (game->collisionCheck(worldClick, UI->stamp) && UI->stampShowing == true && (UI->yesButtonPressed || UI->noButtonPressed))
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

void UImanager::renderPlayingUI(sf::RenderWindow& window, bool passportOpened)
{
	

	yesButton.render(window);
	noButton.render(window);
	nextButton.render(window);

	// Render stamp system
	stampShadow.render(window);
	stamp.render(window);
	stampTab.render(window);

	
}

void UImanager::renderDayEndUI(sf::RenderWindow& window)
{
	dayEndBackground.render(window);
	nextDayButton.render(window);
	
}
