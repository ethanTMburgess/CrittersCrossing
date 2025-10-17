
#include "Game.h"
#include "GameObject.h"
#include "Vector2.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


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

	if (!font.loadFromFile("../Data/Fonts/PixelifySans-Bold.ttf"))
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
	passport.setPosition(100, 205);
	passportPhoto.getImageFromPath("../Data/assets/crossing/critters/frog passport photo.png");


	stamp.getImageFromPath("../Data/assets/crossing/UI/stamp.png");
	stamp.setPosition(570, 90);

	stampTab.getImageFromPath("../Data/assets/crossing/UI/stamp tab.png");
	stampTab.setPosition(stamp.sprite.getPosition().x - 15, stamp.sprite.getPosition().y + 32);	

	stampShadow.getImageFromPath("../Data/assets/crossing/UI/stamp shadow.png");
	stampShadow.setPosition(stamp.sprite.getPosition().x, stamp.sprite.getPosition().y + 70);

	yesStamp.getImageFromPath("../Data/assets/crossing/UI/yes stamp.png");

	noStamp.getImageFromPath("../Data/assets/crossing/UI/no stamp.png");
	

	//                      //                       //                   VARIOUS TEXTS & stamps for passport
	namePPtext.setFont(font);
	namePPtext.setString("NAME:");
	namePPtext.setCharacterSize(9);
	namePPtext.setFillColor(sf::Color(55, 55, 55));
	namePPtext.setPosition(10, 10);

	reasonPPtext.setFont(font);
	reasonPPtext.setString("REASON:");
	reasonPPtext.setCharacterSize(9);
	reasonPPtext.setFillColor(sf::Color(55, 55, 55));
	reasonPPtext.setPosition(10, 10);

	datePPtext.setFont(font);
	datePPtext.setString("DAY:");
	datePPtext.setCharacterSize(9);
	datePPtext.setFillColor(sf::Color(55, 55, 55));	
	datePPtext.setPosition(10, 10);

	yesStamp.setVisible(false);
	noStamp.setVisible(false);

	calendar.getImageFromPath("../Data/assets/crossing/UI/calendar.png");
	calendar.setPosition(283, 79);


	// sounds and music
	if(!buttonPressBuffer.loadFromFile("../Data/assets/sound/keyPress.wav"))
	{
		std::cout << "Error loading button press sound\n";
	}
	buttonPressSound.setBuffer(buttonPressBuffer);

	if(!stampPressBuffer.loadFromFile("../Data/assets/sound/stampSound.wav"))
	{
		std::cout << "Error loading stamp sound\n";
	}
	stampSound.setBuffer(stampPressBuffer);

	if(!BackgroundMusic.openFromFile("../Data/assets/sound/backgroundMusic.wav"))
	{
		std::cout << "Error loading background music\n";
	}
	BackgroundMusic.setLoop(true);
	
	BackgroundMusic.play();
	BackgroundMusic.setVolume(5.f);
	


	sf::Texture& fontTexture = const_cast<sf::Texture&>(font.getTexture(namePPtext.getCharacterSize()));
	fontTexture.setSmooth(false);


	selectCritter();
	
	critter.setPosition(78 - 178, 97);
	sf::Vector2f stampBasePosition = stamp.sprite.getPosition();
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
				stampMoveRight = true;

			}
		}

		sf::Vector2f critterTargetPosition = critter.sprite.getPosition();
		if (critterTargetPosition.x < 78 && critterMoveLeft == false)
		{
			critter.setVector(1, 0);
			critter.setSpeed(3);
			critter.move(critter.getVector()->x * critter.getSpeed(), critter.getVector()->y * critter.getSpeed());
		}
		if (critter.sprite.getPosition().x < 70)
		{
			passport.setPosition(110, 205);
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

		passportPhoto.setPosition(passport.sprite.getPosition().x + 66, passport.sprite.getPosition().y + 5);

		namePPtext.setPosition(passport.sprite.getPosition().x + 5, passport.sprite.getPosition().y + 5);
		reasonPPtext.setPosition(passport.sprite.getPosition().x + 5, passport.sprite.getPosition().y + 25);
		datePPtext.setPosition(passport.sprite.getPosition().x + 5, passport.sprite.getPosition().y + 45);

		yesStamp.setPosition(passport.sprite.getPosition().x + 44, passport.sprite.getPosition().y + 18);
		noStamp.setPosition(passport.sprite.getPosition().x + 44, passport.sprite.getPosition().y + 18);

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

		stampTab.setPosition(stamp.sprite.getPosition().x - 15, stamp.sprite.getPosition().y + 32);
		stampShadow.setPosition(stamp.sprite.getPosition().x, stamp.sprite.getPosition().y + 70);


		float distanceX = stamp.sprite.getPosition().x - passport.sprite.getPosition().x;
		float distanceY = stamp.sprite.getPosition().y - passport.sprite.getPosition().y;

		float toloranceX = 50.f;
		float toloranceY = 50.f;

		sf::Vector2f stampCenter(
			stamp.sprite.getPosition().x + stamp.sprite.getGlobalBounds().width / 2.f,
			stamp.sprite.getPosition().y + stamp.sprite.getGlobalBounds().height / 2.f
		);

		sf::Vector2f passportCenter(
			passport.sprite.getPosition().x + passport.sprite.getGlobalBounds().width / 2.f,
			passport.sprite.getPosition().y + passport.sprite.getGlobalBounds().height / 2.f
		);

		sf::FloatRect stampBounds = stamp.sprite.getGlobalBounds();
		bool passportCenterInStamp = stampBounds.contains(passportCenter);


		if (stampDown && passportCenterInStamp && !stampPressed)
		{
			if (yesButtonPressed)
			{
				yesStamp.setVisible(true);
				noStamp.setVisible(false);
				stampPressed = true;
				yesStampApplied = true;
				noStampApplied = false;
			}
			else if (noButtonPressed)
			{
				noStamp.setVisible(true);
				yesStamp.setVisible(false);
				stampPressed = true;
				noStampApplied = true;
				yesStampApplied = false;
			}
		}

		if (stampDown)
		{
			ButtonTimer += dt;
			if (ButtonTimer >= stampPressedTime)
			{
				stamp.getImageFromPath("../Data/assets/crossing/UI/stamp.png");
				stampDown = false;
				ButtonTimer = 0.0f;

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

	calendar.render(window);

	
	
	if(critter.sprite.getPosition().x  > 65)
	{
		passportPhoto.render(window);
		passport.render(window);

		if (passportOpened)
		{
			window.draw(namePPtext);
			window.draw(reasonPPtext);
			window.draw(datePPtext);

		if (yesStampApplied)
			{
			
				yesStamp.render(window);
			         
			}
		if (noStampApplied)
			{
				noStamp.render(window);
			}
			
		}

	}
	
	

	// passport, photo, and deta render
	

	stampShadow.render(window);
	stamp.render(window);
	stampTab.render(window);
	

	
	
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

		buttonPressSound.play();

		yesButtonDown = true;
		ButtonTimer = 0.0f;

		yesButtonPressed = true;

		noButtonPressed = false;
		

	}

	if (collisionCheck(worldClick, noButton))
	{
		std::cout << "no button clicked\n";
		noButton.getImageFromPath("../Data/assets/crossing/UI/no button pressed.png");

		officeBack.getImageFromPath("../Data/assets/crossing/UI/red office back.png");

		buttonPressSound.play();

		noButtonDown = true;
		ButtonTimer = 0.0f;

		noButtonPressed = true;
		yesButtonPressed = false;
	}


	// next button should only work if a descision has been made by the player

	sf::Vector2f passportPos = passport.sprite.getPosition();
	if (collisionCheck(worldClick, nextButton) && (yesButtonPressed || noButtonPressed) && stampPressed && passportPos.x < 139)	
	{
		
			std::cout << "next button clicked\n";
			nextButton.getImageFromPath("../Data/assets/crossing/UI/next button pressed.png");

			officeBack.getImageFromPath("../Data/assets/crossing/UI/grey office back.png");
			nextButtonPressed = true;
			ButtonTimer = 0.0f;

			buttonPressSound.play();

			// make critter move left off screen
			critterMoveLeft = true;

			yesButtonPressed = false;
			noButtonPressed = false;
			stampPressed = false;
			
			yesStampApplied = false;
			noStampApplied = false;

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


	//////////////////////////////////////////////////////////////////////////////////////////////////////
	if(collisionCheck(worldClick, stampTab) && stampShowing == false )
	{
		std::cout << "stamp tab clicked\n";
		stampMoveLeft = true;

		stampMoveRight = false;

		stampShowing = true;

		
	}

	else if (collisionCheck(worldClick, stampTab) && stampShowing == true)
	{
		std::cout << "stamp tab clicked\n";
		
		stampMoveLeft = false;

		stampMoveRight = true;

		stampShowing = false;

		
		
	}

	if(collisionCheck(worldClick, stamp) && stampShowing == true && (yesButtonPressed || noButtonPressed))
	{
		stampDown = true;
		std::cout << "stamp clicked\n";
		stamp.getImageFromPath("../Data/assets/crossing/UI/stamp pressed.png");
		ButtonTimer = 0.0f;
		
		stampSound.play();
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

	namePPtext.setPosition(static_cast<int>(passport.sprite.getPosition().x + 5), static_cast<int>(passport.sprite.getPosition().y + 5));
	reasonPPtext.setPosition(static_cast<int>(passport.sprite.getPosition().x + 5), static_cast<int>(passport.sprite.getPosition().y + 25));
	datePPtext.setPosition(static_cast<int>(passport.sprite.getPosition().x + 5), static_cast<int>(passport.sprite.getPosition().y + 45));

	return;

	

}

int Game::selectCritter() {
	int chosenCritter = rand() % 5 + 1;

	// Spawns frog
	if (chosenCritter == 1)
	{
		critter.getImageFromPath("../Data/assets/crossing/critters/frog portrait.png");
		isMale = true;
	}

	//spawns mouse
	else if (chosenCritter == 2)
	{
		critter.getImageFromPath("../Data/assets/crossing/critters/mouse portrait.png");
		isMale = true;
	}

	//spawns duck
	else if (chosenCritter == 3)
	{
		critter.getImageFromPath("../Data/assets/crossing/critters/duck portrait.png");
		isMale = true;
	}

	//spawns racoon
	else if (chosenCritter == 4)
	{
		critter.getImageFromPath("../Data/assets/crossing/critters/racoon portrait.png");
		isMale = false;
	}

	//spawns rabbit
	else if (chosenCritter == 5)
	{
		critter.getImageFromPath("../Data/assets/crossing/critters/duck portrait.png");
		isMale = false;
	}

	return chosenCritter;
}

void Game::generatePassportDetails()
{
	if(isMale)
	{
		int SelectFirstName = rand() % 3 + 1;
		firstName = firstNamesM[SelectFirstName];
	}
	else
	{
		int SelectFirstName = rand() % 2 + 1;
		firstName = firstNamesF[SelectFirstName];
	}
	
	
	int SelectlastName = rand() % 5 + 1;

	int SelectReason = rand() % 5 + 1;

	int SelectDay = rand() % 7 + 1;
}






