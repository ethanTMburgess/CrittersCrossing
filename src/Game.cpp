#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


#include "Game.h"
#include "GameObject.h"
#include "Vector2.h"

#include "UImanager.h"

#include "PlayingState.h"
#include "MenuState.h"
#include "DayEndState.h"

#include "GameStateManager.h"






Game::Game(sf::RenderWindow& game_window)
	: window(game_window)
{
	srand(time(NULL));
	UI = new UImanager();
	playing = new PlayingState(this);

}

Game::~Game()
{
	delete UI;
	delete playing;
}

bool Game::init()
{

	currentState = GameState::PLAYING;

	if (!backgroundMusic.openFromFile("../Data/assets/sound/BackgroundMusic.wav"))
	{
		std::cout << "music failed to load\n";
	}
	else
	{
		backgroundMusic.setVolume(5);
		backgroundMusic.setLoop(true);
		backgroundMusic.play();
	}

	if (!font.loadFromFile("../Data/Fonts/PixelifySans-Bold.ttf"))
	{
		std::cerr << "Error loading font\n";
		return false;
	}

	if (!playing->init())
	{
		return false;
	}

	UI->initPlayingUI();

	UImanager* mouseClicked();


	sf::Vector2f stampBasePosition = UI->stamp.sprite.getPosition();


	dayEndBack.getImageFromPath("../data/assets/crossing/UI/day end screen.png");
	dayEndBack.setPosition(0, 0);

	UI->nextDayButton.getImageFromPath("../Data/assets/crossing/UI/power button.png");
	UI->nextDayButton.setPosition(414, 134);


	return true;


}

void Game::update(float dt)
{

	switch (currentState)
	{
	case GameState::MENU:
		updateMenu(dt);
		break;

	case GameState::PLAYING:
		playing->update(dt);
		break;

	case GameState::DAYEND:
		updateDayEnd(dt);
		break;

	default:
		break;
	}



}

void Game::render()
{



	switch (currentState)
	{
	case GameState::MENU:
		renderMenu();
		break;

	case GameState::PLAYING:
		playing->render(window);
		UI->renderUI(window, playing->passportOpened);
		break;

	case GameState::DAYEND:
		renderDayEnd();
		break;

	}






}







void Game::mousePressed(sf::Event event)
{
	sf::Vector2i pixelClick{ event.mouseButton.x, event.mouseButton.y };
	sf::Vector2f worldClick = window.mapPixelToCoords(pixelClick);

	if (playing->collisionCheck(worldClick, playing->passport))
	{
		objectDragged = &playing->passport;

		sf::Sprite* sprite = objectDragged->getSprite();
		sf::Vector2f objectPos = sprite->getPosition();
		dragOffset = worldClick - objectPos;

		passportDragged = true;
		std::cout << "presssssed\n";
	}
}

void Game::mouseMoved(sf::Event event)
{

	if (objectDragged && passportDragged)
	{
		sf::Vector2i pixelPos{ event.mouseMove.x, event.mouseMove.y };
		sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

		// will pull the object based on mouse. offset should allow for the passport to not snap
		objectDragged->setPosition(worldPos.x - dragOffset.x, (worldPos.y - dragOffset.y - 5));

		std::cout << "drraaaaaagged\n";

		sf::Vector2f passportPos = playing->passport.sprite.getPosition();

		// if passport is dragged far enough up, it opens. if dragged back down, it closes
		if (passportPos.x > 259 && playing->passportOpened == false)
		{


			playing->passport.getImageFromPath("../Data/assets/crossing/UI/passport.png");
			playing->passportOpened = true;

		}


		else if (passportPos.x <= 259 - 117 && playing->passportOpened == true)
		{

			playing->passport.getImageFromPath("../Data/assets/crossing/UI/closed passport.png");
			playing->passportOpened = false;
		}


	}


}

void Game::mouseReleased(sf::Event event)
{

	if (passportDragged == true)
	{
		sf::Vector2 currentPos = playing->passport.sprite.getPosition();
		playing->passport.setPosition(currentPos.x, currentPos.y + 5);
	}


	objectDragged = nullptr;

	passportDragged = false;



	std::cout << "releaaaaased\n";

	playing->namePPtext.setPosition(static_cast<int>(playing->passport.sprite.getPosition().x + 5), static_cast<int>(playing->passport.sprite.getPosition().y + 5));
	playing->reasonPPtext.setPosition(static_cast<int>(playing->passport.sprite.getPosition().x + 5), static_cast<int>(playing->passport.sprite.getPosition().y + 25));
	playing->dayPPtext.setPosition(static_cast<int>(playing->passport.sprite.getPosition().x + 5), static_cast<int>(playing->passport.sprite.getPosition().y + 45));

	return;



}





void Game::newDay()
{
	playing->crittersSeen = 0;

	// adds a new day, loops back to 0 after sunday
	if (currentDay < 6)
	{

		std::cout << "--------------------\nNew Day!\n";
		currentDay++;
	}
	else
	{
		currentDay = 0;
	}
	money = money + dayScore * 5;
	std::cout << "\n\n------------\n\nDay Score: " << dayScore << "\nTotal Money: $" << money << "\n\n------------\n\n" << std::endl;



}







void Game::renderMenu()
{

}



void Game::renderDayEnd()
{
	dayEndBack.render(window);
	UI->nextDayButton.render(window);
}

void Game::updateMenu(float dt)
{
	// Simple placeholder for now:
	// Check for "start game" button or condition to move to playing state
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		std::cout << "Starting game..." << std::endl;

	}
}



void Game::updateDayEnd(float dt)
{
	static float timer = 0.0f;




	std::cout << "Day End! Preparing next day..." << std::endl;


	newDay();





}






