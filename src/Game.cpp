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
	uiManager = new UImanager();

}

Game::~Game()
{
	delete uiManager;
}

bool Game::init()
{

	currentState = GameState::PLAYING;


	if (!font.loadFromFile("../Data/Fonts/PixelifySans-Bold.ttf"))
	{
		std::cerr << "Error loading font\n";
		return false;
	}


	UImanager* mouseClicked();

	





	officeBack.getImageFromPath("../Data/assets/crossing/UI/grey office back.png");
	officeBack.setPosition(0, 0);

	background.getImageFromPath("../Data/assets/crossing/UI/crossing background.png");
	background.setPosition(0, 0);
	//yes button
	uiManager->yesButton.getImageFromPath("../Data/assets/crossing/UI/yes button.png");
	uiManager->yesButton.setPosition(290 - 5, 20);
	//no button
	uiManager->noButton.getImageFromPath("../Data/assets/crossing/UI/no button.png");
	uiManager->noButton.setPosition(390 - 15, 20);
	//next button
	uiManager->nextButton.getImageFromPath("../Data/assets/crossing/UI/next button.png");
	uiManager->nextButton.setPosition(490 - 10, 20);

	//passport
	passport.getImageFromPath("../Data/assets/crossing/UI/closed passport.png");
	passport.setPosition(100, 205);
	passportPhoto.getImageFromPath("../Data/assets/crossing/critters/frog passport photo.png");


	uiManager->stamp.getImageFromPath("../Data/assets/crossing/UI/stamp.png");
	uiManager->stamp.setPosition(570, 90);

	uiManager->stampTab.getImageFromPath("../Data/assets/crossing/UI/stamp tab.png");
	uiManager->stampTab.setPosition(uiManager->stamp.sprite.getPosition().x - 15, uiManager->stamp.sprite.getPosition().y + 32);

	uiManager->stampShadow.getImageFromPath("../Data/assets/crossing/UI/stamp shadow.png");
	uiManager->stampShadow.setPosition(uiManager->stamp.sprite.getPosition().x, uiManager->stamp.sprite.getPosition().y + 70);

	uiManager->yesStamp.getImageFromPath("../Data/assets/crossing/UI/yes stamp.png");

	uiManager->noStamp.getImageFromPath("../Data/assets/crossing/UI/no stamp.png");


	speechBubble.getImageFromPath("../Data/assets/crossing/UI/speech bubble.png");
	speechBubble.setPosition(80, 57);




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

	dayPPtext.setFont(font);
	dayPPtext.setString("DAY:");
	dayPPtext.setCharacterSize(9);
	dayPPtext.setFillColor(sf::Color(55, 55, 55));
	dayPPtext.setPosition(10, 10);



	nameSpeechText.setFont(font);
	nameSpeechText.setString(nameDialogue);
	nameSpeechText.setCharacterSize(10);
	nameSpeechText.setFillColor(sf::Color(55, 55, 55));
	nameSpeechText.setPosition(speechBubble.sprite.getPosition().x + 5, speechBubble.sprite.getPosition().y + 3);

	reasonSpeechText.setFont(font);
	reasonSpeechText.setString(reasonDialogue);
	reasonSpeechText.setCharacterSize(10);
	reasonSpeechText.setFillColor(sf::Color(55, 55, 55));
	reasonSpeechText.setPosition(speechBubble.sprite.getPosition().x + 5, speechBubble.sprite.getPosition().y + 17);



	uiManager->yesStamp.setVisible(false);
	uiManager->noStamp.setVisible(false);

	calendar.getImageFromPath("../Data/assets/crossing/UI/calendar.png");
	calendar.setPosition(283, 79);

	calendarText.setFont(font);
	calendarText.setString(daysOfWeek[currentDay]);
	calendarText.setCharacterSize(15);
	calendarText.setFillColor(sf::Color(55, 55, 55));
	calendarText.setPosition(calendar.sprite.getPosition().x + 13, calendar.sprite.getPosition().y + 3);




	// sounds and music
	if (!buttonPressBuffer.loadFromFile("../Data/assets/sound/keyPress.wav"))
	{
		std::cout << "Error loading button press sound\n";
	}
	buttonPressSound.setBuffer(buttonPressBuffer);

	if (!stampPressBuffer.loadFromFile("../Data/assets/sound/stampSound.wav"))
	{
		std::cout << "Error loading stamp sound\n";
	}
	stampSound.setBuffer(stampPressBuffer);

	if (!BackgroundMusic.openFromFile("../Data/assets/sound/backgroundMusic.wav"))
	{
		std::cout << "Error loading background music\n";
	}
	BackgroundMusic.setLoop(true);

	BackgroundMusic.play();
	BackgroundMusic.setVolume(5.f);






	selectCritter();

	critter.setPosition(78 - 178, 97);
	sf::Vector2f stampBasePosition = uiManager->stamp.sprite.getPosition();


	dayEndBack.getImageFromPath("../data/assets/crossing/UI/day end screen.png");
	dayEndBack.setPosition(0, 0);

	uiManager->nextDayButton.getImageFromPath("../Data/assets/crossing/UI/power button.png");
	uiManager->nextDayButton.setPosition(414, 134);


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
		updatePlaying(dt);
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
				renderPlaying();
				break;

			case GameState::DAYEND:
				renderDayEnd();
				break;

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
	dayPPtext.setPosition(static_cast<int>(passport.sprite.getPosition().x + 5), static_cast<int>(passport.sprite.getPosition().y + 45));

	return;



}

int Game::selectCritter() {

	if (crittersSeen >= crittersPerDay)
	{
		newDay();
	}

	int chosenCritter = rand() % 5 + 1;
	currentCritter = chosenCritter;

	// Spawns frog
	if (chosenCritter == 1)
	{
		critter.getImageFromPath("../Data/assets/crossing/critters/frog portrait.png");

		isMale = true;
		firstName = "Fred";
		lastName = "Hopperton";

	}

	//spawns mouse
	else if (chosenCritter == 2)
	{
		critter.getImageFromPath("../Data/assets/crossing/critters/mouse portrait.png");

		isMale = true;
		firstName = "Stuart";
		lastName = "Whiskerfield";

	}

	//spawns duck
	else if (chosenCritter == 3)
	{
		critter.getImageFromPath("../Data/assets/crossing/critters/duck portrait.png");

		isMale = true;
		firstName = "Quincy";
		lastName = "Featherson";

	}

	//spawns racoon
	else if (chosenCritter == 4)
	{
		critter.getImageFromPath("../Data/assets/crossing/critters/racoon portrait.png");

		isMale = false;
		firstName = "Luna";
		lastName = "Snuffleson";

	}

	//spawns rabbit
	else if (chosenCritter == 5)
	{
		critter.getImageFromPath("../Data/assets/crossing/critters/rabbit portrait.png");

		isMale = false;
		firstName = "Willow";
		lastName = "Cottontail";

	}

	passportPhoto.getImageFromPath(passportPhotos[chosenCritter - 1]);

	if (!hasGeneratedDialougeDetails)
	{
		generateDialougeDetails();
		hasGeneratedDialougeDetails = true;
	}

	if (!hasGeneratedPassportDetails)
	{
		generatePassportDetails();
		hasGeneratedPassportDetails = true;
	}

	return chosenCritter;
}

void Game::generateDialougeDetails()
{

	// generate reason for entry
	int selectReason = rand() % 5;
	newReason = reasons[selectReason];
	reasonDialoge = reasonsShort[selectReason];

	while (newReason == lastReason)
	{
		int selectReason = rand() % 5;
		newReason = reasons[selectReason];
	}




	reason = newReason;


	lastReason = reason;


	nameDialogue = "My name is " + firstName + " " + lastName;
	reasonDialogue = "I am heading into town to " + reason;

	std::cout << nameDialogue << std::endl;
	std::cout << reasonDialogue << std::endl;
}

void Game::generatePassportDetails()
{
	int missmatchChance = rand() % 8;

	passportFirstName = firstName;
	passportLastName = lastName;
	passportReason = reasonDialoge;
	passportDay = daysOfWeek[currentDay];



	// Changes name on passport to be incorrect
	if (missmatchChance == 1)
	{
		std::cout << "------------------\nname mismatch\n";

		if (isMale)
		{
			int selectFirstName = rand() % 3;
			passportFirstName = firstNamesM[selectFirstName];

			while (passportFirstName == firstName)
			{
				selectFirstName = rand() % 3;
				passportFirstName = firstNamesM[selectFirstName];
			}
		}
		else
		{
			int selectFirstName = rand() % 2;
			passportFirstName = firstNamesF[selectFirstName];

			while (passportFirstName == firstName)
			{
				selectFirstName = rand() % 2;
				passportFirstName = firstNamesF[selectFirstName];
			}
		}

		int selectLastName = rand() % 5;
		passportLastName = lastNames[selectLastName];

		while (passportLastName == lastName)
		{
			selectLastName = rand() % 5;
			passportLastName = lastNames[selectLastName];
		}

		passportValid = false;
	}

	// Changes reason on passport to be incorrect
	else if (missmatchChance == 2)
	{
		std::cout << "-------------------\nreason mismatch - DENY\n";

		int selectReason = rand() % 5;
		passportReason = reasonsShort[selectReason];

		while (passportReason == reasonDialoge)
		{
			selectReason = rand() % 5;
			passportReason = reasonsShort[selectReason];
		}

		passportValid = false;
	}

	// Changes day on passport to be incorrect
	else if (missmatchChance == 3)
	{
		std::cout << "--------------------\nday mismatch - DENY\n";

		int selectDay = rand() % 7;
		passportDay = daysOfWeek[selectDay];

		while (passportDay == daysOfWeek[currentDay])
		{
			selectDay = rand() % 7;
			passportDay = daysOfWeek[selectDay];
		}

		passportValid = false;
	}

	// Changes photo on the passport to be incorrect
	else if (missmatchChance == 4)
	{
		{
			std::cout << "--------------------\nphoto mismatch - DENY\n";

			int selectPhoto = rand() % 5;


			while (selectPhoto == (currentCritter - 1))
			{
				selectPhoto = rand() % 5;
			}

			passportPhoto.getImageFromPath(passportPhotos[selectPhoto]);
		}

		passportValid = false;

	}

	// if no problems are generated, the critter should be accepted
	else
	{
		std::cout << "--------------------\nAll correct - APPROVE\n";

		passportDay = daysOfWeek[currentDay];

		passportValid = true;

	}


	namePPtext.setString(passportFirstName + "\n" + passportLastName);
	reasonPPtext.setString(passportReason);
	dayPPtext.setString(passportDay);
}

void Game::newDay()
{
	crittersSeen = 0;

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

void Game::renderPlaying()
{



	// office back shows behind the main game backgroudnd
	officeBack.render(window);

	critter.render(window);


	background.render(window);

	// buttons render
	uiManager->yesButton.render(window);
	uiManager->noButton.render(window);
	uiManager->nextButton.render(window);

	calendar.render(window);
	window.draw(calendarText);

	if (critterInPosition)
	{
		speechBubble.render(window);
		window.draw(nameSpeechText);
		window.draw(reasonSpeechText);
	}


	if (critter.sprite.getPosition().x > 65)
	{
		passportPhoto.render(window);
		passport.render(window);

		if (passportOpened)
		{
			window.draw(namePPtext);
			window.draw(reasonPPtext);
			window.draw(dayPPtext);

			if (uiManager->yesStampApplied)
			{

				uiManager->yesStamp.render(window);

			}
			if (uiManager->noStampApplied)
			{
				uiManager->noStamp.render(window);
			}

		}

	}



	// passport, photo, and deta render


	uiManager->stampShadow.render(window);
	uiManager->stamp.render(window);
	uiManager->stampTab.render(window);





}

void Game::renderDayEnd()
{
	dayEndBack.render(window);
	uiManager->nextDayButton.render(window);
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

void Game::updatePlaying(float dt)
{

	sf::Texture& fontTexture = const_cast<sf::Texture&>(font.getTexture(namePPtext.getCharacterSize()));
	fontTexture.setSmooth(false);

	// track if button has been pressed
	if (uiManager->yesButtonDown)
	{
		uiManager->ButtonTimer += dt;
		if (uiManager->ButtonTimer >= ButtonPressedTime)
		{
			uiManager->yesButton.getImageFromPath("../Data/assets/crossing/UI/yes button.png");
			uiManager->yesButtonDown = false;
			uiManager->ButtonTimer = 0.0f;

		}
	}

	// track if button has been pressed
	if (uiManager->noButtonDown)
	{
		uiManager->ButtonTimer += dt;
		if (uiManager->ButtonTimer >= ButtonPressedTime)
		{
			uiManager->noButton.getImageFromPath("../Data/assets/crossing/UI/no button.png");
			uiManager->noButtonDown = false;
			uiManager->ButtonTimer = 0.0f;
		}
	}

	// track if button has been pressed
	if (uiManager->nextButtonPressed)
	{

		uiManager->ButtonTimer += dt;
		if (uiManager->ButtonTimer >= ButtonPressedTime)
		{
			uiManager->nextButton.getImageFromPath("../Data/assets/crossing/UI/next button.png");
			uiManager->nextButtonPressed = false;
			uiManager->ButtonTimer = 0.0f;
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
	else if (critterTargetPosition.x >= 78 && !critterMoveLeft)
	{
		critter.setSpeed(0);
		critterInPosition = true;
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


			if (crittersSeen >= crittersPerDay)
			{
				std::cout << "game state changed\n";

			}
			else
			{
				selectCritter();
				critterMoveLeft = false;

			}

		}
	}

	passportPhoto.setPosition(passport.sprite.getPosition().x + 67, passport.sprite.getPosition().y + 5);

	namePPtext.setPosition(passport.sprite.getPosition().x + 5, passport.sprite.getPosition().y + 3);
	reasonPPtext.setPosition(passport.sprite.getPosition().x + 5, passport.sprite.getPosition().y + 30);
	dayPPtext.setPosition(passport.sprite.getPosition().x + 5, passport.sprite.getPosition().y + 45);

	uiManager->yesStamp.setPosition(passport.sprite.getPosition().x + 44, passport.sprite.getPosition().y + 18);
	uiManager->noStamp.setPosition(passport.sprite.getPosition().x + 44, passport.sprite.getPosition().y + 18);

	if (stampMoveLeft)
	{
		uiManager->stamp.setVector(-1, 0);
		uiManager->stamp.setSpeed(stampSpeed);
		uiManager->stamp.move(uiManager->stamp.getVector()->x * uiManager->stamp.getSpeed(), uiManager->stamp.getVector()->y * uiManager->stamp.getSpeed());

		if (uiManager->stamp.sprite.getPosition().x <= stampVisible)
		{
			uiManager->stamp.setPosition(stampVisible, 90);
			stampMoveLeft = false;
			stampShowing = true;
		}
	}

	if (stampMoveRight)
	{
		uiManager->stamp.setVector(1, 0);
		uiManager->stamp.setSpeed(stampSpeed);
		uiManager->stamp.move(uiManager->stamp.getVector()->x * uiManager->stamp.getSpeed(), uiManager->stamp.getVector()->y * uiManager->stamp.getSpeed());

		if (uiManager->stamp.sprite.getPosition().x >= stampHidden)
		{
			uiManager->stamp.setPosition(stampHidden, 90);
			stampMoveLeft = false;
			stampShowing = false;
		}

	}

	uiManager->stampTab.setPosition(uiManager->stamp.sprite.getPosition().x - 15, uiManager->stamp.sprite.getPosition().y + 32);
	uiManager->stampShadow.setPosition(uiManager->stamp.sprite.getPosition().x, uiManager->stamp.sprite.getPosition().y + 70);


	float distanceX = uiManager->stamp.sprite.getPosition().x - passport.sprite.getPosition().x;
	float distanceY = uiManager->stamp.sprite.getPosition().y - passport.sprite.getPosition().y;

	float toloranceX = 50.f;
	float toloranceY = 50.f;

	sf::Vector2f stampCenter(
		uiManager->stamp.sprite.getPosition().x + uiManager->stamp.sprite.getGlobalBounds().width / 2.f,
		uiManager->stamp.sprite.getPosition().y + uiManager->stamp.sprite.getGlobalBounds().height / 2.f
	);

	sf::Vector2f passportCenter(
		passport.sprite.getPosition().x + passport.sprite.getGlobalBounds().width / 2.f,
		passport.sprite.getPosition().y + passport.sprite.getGlobalBounds().height / 2.f
	);

	sf::FloatRect stampBounds = uiManager->stamp.sprite.getGlobalBounds();
	bool passportCenterInStamp = stampBounds.contains(passportCenter);


	if (uiManager->stampDown && passportCenterInStamp && !uiManager->stampPressed)
	{
		if (uiManager->yesButtonPressed)
		{
			uiManager->yesStamp.setVisible(true);
			uiManager->noStamp.setVisible(false);
			uiManager->stampPressed = true;
			uiManager->yesStampApplied = true;
			uiManager->noStampApplied = false;
		}
		else if (uiManager->noButtonPressed)
		{
			uiManager->noStamp.setVisible(true);
			uiManager->yesStamp.setVisible(false);
			uiManager->stampPressed = true;
			uiManager->noStampApplied = true;
			uiManager->yesStampApplied = false;
		}
	}

	if (uiManager->stampDown)
	{
		uiManager->ButtonTimer += dt;
		if (uiManager->ButtonTimer >= stampPressedTime)
		{
			uiManager->stamp.getImageFromPath("../Data/assets/crossing/UI/stamp.png");
			uiManager->stampDown = false;
			uiManager->ButtonTimer = 0.0f;

		}
	}







	nameSpeechText.setString(nameDialogue);
	reasonSpeechText.setString(reasonDialogue);
	calendarText.setString(daysOfWeek[currentDay]);




}

void Game::updateDayEnd(float dt)
{
	static float timer = 0.0f;




	std::cout << "Day End! Preparing next day..." << std::endl;


	newDay();





}






