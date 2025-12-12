#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Time.hpp>

#include <Windows.h>
#include <cmath>

#include "Game.h"
#include "GameObject.h"
#include "Vector2.h"
#include "UImanager.h"
#include "PlayingState.h"



UImanager::UImanager() 
{


	playing = nullptr;
	game = nullptr;

	

}




bool UImanager::initPlayingUI()
{

	passportValid = false;

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

	mistakeCounterText.setFont(game->getFont());
	mistakeCounterText.setCharacterSize(16);
	mistakeCounterText.setFillColor(game->getTextColor());
	mistakeCounterText.setPosition(15, 15);
	mistakeCounterText.setString("Mistakes: " + std::to_string(mistakesCounter));





	return true;
}







bool UImanager::initdayEndUI()
{
	nextDayButton.getImageFromPath("../Data/assets/crossing/UI/power button.png");
	nextDayButton.setPosition(412, 130);
	return true;
}


bool UImanager::initMenuUI()
{
	playButton.getImageFromPath("../Data/assets/crossing/UI/yes button.png");
	playButton.setPosition(160, 200);

	quitButton.getImageFromPath("../Data/assets/crossing/UI/no button.png");
	quitButton.setPosition(playButton.sprite.getPosition().x + 200, playButton.sprite.getPosition().y);

	return true;
}


void UImanager::mouseClicked(sf::RenderWindow& window, sf::Event event)
{

	if (!game)
	{
		std::cout << "UImanager: game is null!" << std::endl;
		return;
	}

	if (!playing)
	{
		std::cout << "UImanager: playing is null!" << std::endl;
		return;
	}




	//get the click position
	sf::Vector2i pixelClick{ event.mouseButton.x, event.mouseButton.y };
	sf::Vector2f worldClick = window.mapPixelToCoords(pixelClick);

	if (game->currentState == GameState::PLAYING)
	{



		if (game->collisionCheck(worldClick, yesButton) && playing->critterInPosition == true)
		{

			std::cout << "yes button clicked\n";
			yesButton.getImageFromPath("../Data/assets/crossing/UI/yes button pressed.png");

			officeBack.getImageFromPath("../Data/assets/crossing/UI/green office back.png");

			
			playing->buttonPressSound.play();

			yesButtonDown = true;
			ButtonTimer = 0.0f;

			yesButtonPressed = true;

			noButtonPressed = false;


		}

		if (game->collisionCheck(worldClick, nextDayButton))
		{

		}

		if (game->collisionCheck(worldClick, noButton) && playing->critterInPosition == true)
		{
			std::cout << "no button clicked\n";
			noButton.getImageFromPath("../Data/assets/crossing/UI/no button pressed.png");

			officeBack.getImageFromPath("../Data/assets/crossing/UI/red office back.png");

			playing->buttonPressSound.play();

			noButtonDown = true;
			ButtonTimer = 0.0f;

			noButtonPressed = true;
			yesButtonPressed = false;
		}


		bool hasValidPassport = false;


		// next button should only work if a descision has been made by the player

		sf::Vector2f passportPos = playing->passport.sprite.getPosition();
		if (game->collisionCheck(worldClick, nextButton) && (yesButtonPressed || noButtonPressed) && stampPressed && passportPos.x < 139)
		{

			std::cout << "next button clicked\n";
			nextButton.getImageFromPath("../Data/assets/crossing/UI/next button pressed.png");


			officeBack.getImageFromPath("../Data/assets/crossing/UI/grey office back.png");
			nextButtonPressed = true;
			ButtonTimer = 0.0f;

			dayScore = game->getDayScore();

			if (noButtonPressed && playing->passportValid)
			{
				std::cout << "passport was valid but denied\n";
				dayScore = dayScore - 1;
				mistakesCounter--;
			}

			else if (noButtonPressed && !playing->passportValid)
			{
				std::cout << "passport was invalid and denied\n";
				dayScore = dayScore + 1;
			}

			else if (yesButtonPressed && !playing->passportValid)
			{
				std::cout << "passport was invalid but allowed\n";
				dayScore = dayScore - 1;
				mistakesCounter--;
			}

			else if (yesButtonPressed && playing->passportValid)
			{
				std::cout << "passport was valid and allowed\n";
				dayScore = dayScore + 1;
				
			}

			game->setDayScore(dayScore);

			playing->buttonPressSound.play();

			// make critter move left off screen
			playing->critterMoveLeft = true;

			yesButtonPressed = false;
			noButtonPressed = false;
			stampPressed = false;

			yesStampApplied = false;
			noStampApplied = false;

			playing->hasGeneratedDialougeDetails = false;
			playing->hasGeneratedPassportDetails = false;

			playing->critterInPosition = false;
		}

		else if (game->collisionCheck(worldClick, nextButton))
		{
			std::cout << "select [yes / no]\n";
		}

		if (game->collisionCheck(worldClick, playing->passport))
		{
			std::cout << "passport clicked\n";
			playing->hover = true;
		}


		//////////////////////////////////////////////////////////////////////////////////////////////////////
		if (game->collisionCheck(worldClick, stampTab) && stampShowing == false)
		{
			std::cout << "stamp tab clicked\n";
			stampMoveLeft = true;
			stampMoveRight = false;
			stampShowing = true;
		}

		else if (game->collisionCheck(worldClick, stampTab) && stampShowing == true)
		{
			std::cout << "stamp tab clicked\n";
			stampMoveLeft = false;
			stampMoveRight = true;
			stampShowing = false;
		}

		if (game->collisionCheck(worldClick, stamp) && stampShowing == true && (yesButtonPressed || noButtonPressed) && game->currentState == GameState::PLAYING)
		{
			stampDown = true;
			std::cout << "stamp clicked\n";
			stamp.getImageFromPath("../Data/assets/crossing/UI/stamp pressed.png");
			ButtonTimer = 0.0f;
			playing->stampSound.play();
		}

	}

	if (game->currentState == GameState::DAYEND)
	{
		if (game->collisionCheck(worldClick, nextDayButton))
		{
			game->currentState = GameState::PLAYING;
		}
	}
	

	if (game->currentState == GameState::MENU)
	{
		if (game->collisionCheck(worldClick, playButton))
		{
			playButton.getImageFromPath("../Data/assets/crossing/UI/yes button pressed.png");
			ButtonTimer = 0.0f;
			game->currentState = GameState::PLAYING;
		}

		if (game->collisionCheck(worldClick, quitButton))
		{
			std::cout << "quit button pressed\n";
			playButton.getImageFromPath("../Data/assets/crossing/UI/no button pressed.png");
			ButtonTimer = 0.0f;
			exit(0);
		}
	}
}

void UImanager::UpdateUI(float dt, const sf::Vector2f& passportPos, bool passportOpened)
{
	stampTab.setPosition(stamp.sprite.getPosition().x - 15, stamp.sprite.getPosition().y + 32);
	stampShadow.setPosition(stamp.sprite.getPosition().x, stamp.sprite.getPosition().y + 70);
	mistakeCounterText.setString("Mistakes Remaining: " + std::to_string(getMistakesCounter()));
	mistakeCounterText.setFillColor(game->getTextColor());
	mistakeCounterText.setPosition(5, 5);

	// prints forever (debugging)
	// 
	// std::cout << mistakesCounter << std::endl;

	if (mistakesCounter <= 0)
	{
		mistakesCounter = 3;
		std::cout << "too many mistakes, returning to menu\n";
		game->setCurrentDay(0);
		game->setDayScore(0);
		playing->crittersSeen = 0;
		game->setState(GameState::MENU);
	}
	
	
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

	
	stampShadow.render(window);
	stamp.render(window);
	stampTab.render(window);

	window.draw(mistakeCounterText);
}

void UImanager::renderDayEndUI(sf::RenderWindow& window)
{
	dayEndBackground.render(window);
	nextDayButton.render(window);
}

void UImanager::renderMenuUI(sf::RenderWindow& window)
{
	playButton.render(window);
	quitButton.render(window);
}