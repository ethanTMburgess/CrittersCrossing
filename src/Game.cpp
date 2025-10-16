
#include "Game.h"
#include "GameObject.h"
#include "Vector2.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>


Game::Game(sf::RenderWindow& game_window)
	: window(game_window)
{
	srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{

	if (!font.loadFromFile("../Data/Fonts/BMmini.ttf"))
	{
		std::cerr << "Error loading font\n";
		return false;
	}



	officeBack.getImageFromPath("../Data/assets/crossing/UI/grey office back.png");
	officeBack.setPosition(0, 0);

	background.getImageFromPath("../Data/assets/crossing/UI/crossing background.png");
	background.setPosition(0, 0);
	//yes button
	yesButton.getImageFromPath("../Data/assets/crossing/UI/yes button.png");
	yesButton.setPosition(290 - 5, 20);
	//no button
	noButton.getImageFromPath("../Data/assets/crossing/UI/no button.png");
	noButton.setPosition(390 - 15, 20);
	//next button
	nextButton.getImageFromPath("../Data/assets/crossing/UI/next button.png");
	nextButton.setPosition(490 - 10, 20);

	//passport
	passport.getImageFromPath("../Data/assets/crossing/UI/closed passport.png");
	passport.setPosition(130, 205);

	selectCritter();
	
	critter.setPosition(78 - 178, 97);
	return true;
}

void Game::update(float dt)
{

	
	
	if (inMenu == false) 
	{
		// track if button has been pressed
		if (yesButtonDown)
		{
			ButtonTimer += dt;
			if (ButtonTimer >= ButtonPressedTime)
			{
				yesButton.getImageFromPath("../Data/assets/crossing/UI/yes button.png");
				yesButtonDown = false;
				ButtonTimer = 0.0f;
				
			}
		}

		// track if button has been pressed
		if (noButtonDown)
		{
			ButtonTimer += dt;
			if (ButtonTimer >= ButtonPressedTime)
			{
				noButton.getImageFromPath("../Data/assets/crossing/UI/no button.png");
				noButtonDown = false;
				ButtonTimer = 0.0f;
			}
		}

		// track if button has been pressed
		if (nextButtonPressed)
		{
			
			ButtonTimer += dt;
			if (ButtonTimer >= ButtonPressedTime)
			{
				nextButton.getImageFromPath("../Data/assets/crossing/UI/next button.png");
				nextButtonPressed = false;
				ButtonTimer = 0.0f;
			}
		}

		sf::Vector2f targetPosition = critter.sprite.getPosition();
		if (targetPosition.x < 78 && critterMoveLeft == false) 
		{
			critter.setVector(1, 0);
			critter.setSpeed(3);
			critter.move(critter.getVector()->x * critter.getSpeed(), critter.getVector()->y * critter.getSpeed());
		}
		if(critter.sprite.getPosition().x < 70)
		{
			passport.setPosition(130, 205);
			if (passport.sprite.getPosition().x <= 259 - 117 && passportOpened == true)
			{

				passport.getImageFromPath("../Data/assets/crossing/UI/closed passport.png");
				passportOpened = false;
			}
		}
		
		
		

		if (critterMoveLeft)
		{
			critter.setVector(-1, 0);
			critter.setSpeed(3);
			critter.move(critter.getVector()->x * critter.getSpeed(), critter.getVector()->y * critter.getSpeed());
			

			// stop when completely off the left side of the screen
			if (critter.sprite.getPosition().x + critter.sprite.getGlobalBounds().width < 0.0f)
			{
				selectCritter();
				critterMoveLeft = false;
			}
		}
		



	}

	

}

void Game::render()
{
	// office back shows behind the main game backgroudnd
	officeBack.render(window);

	critter.render(window);

	
	background.render(window);

	// buttons render
	yesButton.render(window);
	noButton.render(window);
	nextButton.render(window);

	



	passport.render(window);
}

void Game::mouseClicked(sf::Event event)
{
	//get the click position
	sf::Vector2i pixelClick{ event.mouseButton.x, event.mouseButton.y };
	sf::Vector2f worldClick = window.mapPixelToCoords(pixelClick);

	if (collisionCheck(worldClick, yesButton))
	{

		std::cout << "yes button clicked\n";
		yesButton.getImageFromPath("../Data/assets/crossing/UI/yes button pressed.png");

		officeBack.getImageFromPath("../Data/assets/crossing/UI/green office back.png");
		yesButtonDown = true;
		ButtonTimer = 0.0f;

		yesButtonPressed = true;

		

	}

	if (collisionCheck(worldClick, noButton))
	{
		std::cout << "no button clicked\n";
		noButton.getImageFromPath("../Data/assets/crossing/UI/no button pressed.png");

		officeBack.getImageFromPath("../Data/assets/crossing/UI/red office back.png");
		noButtonDown = true;
		ButtonTimer = 0.0f;

		noButtonPressed = true;
	}

	// next button should only work if a descision has been made by the player
	if (collisionCheck(worldClick, nextButton) && (yesButtonPressed || noButtonPressed))	
	{
		
			std::cout << "next button clicked\n";
			nextButton.getImageFromPath("../Data/assets/crossing/UI/next button pressed.png");

			officeBack.getImageFromPath("../Data/assets/crossing/UI/grey office back.png");
			nextButtonPressed = true;
			ButtonTimer = 0.0f;

			// make critter move left off screen
			critterMoveLeft = true;

			yesButtonPressed = false;
			noButtonPressed = false;
	}
	else if(collisionCheck(worldClick, nextButton))
	{
		std::cout << "select [yes / no]\n";
	}

	if (collisionCheck(worldClick, passport))
	{
		std::cout << "passport clicked\n";
		hover = true;

	}


}
bool Game::collisionCheck(const sf::Vector2f& click, GameObject& object)
{
	
	sf::Sprite* sprite = object.getSprite();
	sf::FloatRect bounds = sprite->getGlobalBounds();
	return bounds.contains(static_cast<float>(click.x), static_cast<float>(click.y));
}

void Game::mousePressed(sf::Event event)
{
	sf::Vector2i pixelClick{ event.mouseButton.x, event.mouseButton.y };
	sf::Vector2f worldClick = window.mapPixelToCoords(pixelClick);

	if (collisionCheck(worldClick, passport))
	{
		objectDragged = &passport;

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

		sf::Vector2f passportPos = passport.sprite.getPosition();

		// if passport is dragged far enough up, it opens. if dragged back down, it closes
		if (passportPos.x > 259 && passportOpened == false)
		{

			
			passport.getImageFromPath("../Data/assets/crossing/UI/passport.png");
			passportOpened = true;
			
		}


		else if (passportPos.x <= 259 - 117 && passportOpened == true)
		{
			
			passport.getImageFromPath("../Data/assets/crossing/UI/closed passport.png");
			passportOpened = false;
		}


	}


}

void Game::mouseReleased(sf::Event event)
{

	if (passportDragged == true)
	{
		sf::Vector2 currentPos = passport.sprite.getPosition();
		passport.setPosition(currentPos.x, currentPos.y + 5);
	}


	objectDragged = nullptr;

	passportDragged = false;



	std::cout << "releaaaaased\n";

	return;

	

}

int Game::selectCritter() {
	int chosenCritter = rand() % 5 + 1;

	// Spawns frog
	if (chosenCritter == 1)
	{
		critter.getImageFromPath("../Data/assets/crossing/critters/frog portrait.png");
	}

	//spawns mouse
	else if (chosenCritter == 2)
	{
		critter.getImageFromPath("../Data/assets/crossing/critters/mouse portrait.png");
	}

	//spawns duck
	else if (chosenCritter == 3)
	{
		critter.getImageFromPath("../Data/assets/crossing/critters/duck portrait.png");
	}

	//spawns racoon
	else if (chosenCritter == 4)
	{
		critter.getImageFromPath("../Data/assets/crossing/critters/racoon portrait.png");
	}

	//spawns rabbit
	else if (chosenCritter == 5)
	{
		critter.getImageFromPath("../Data/assets/crossing/critters/duck portrait.png");
	}

	return chosenCritter;
}





