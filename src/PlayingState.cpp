#include "PlayingState.h"
#include "Game.h"
#include "UImanager.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

PlayingState::PlayingState(Game* game) : game(game)
{
	srand(time(NULL));
	UI = game->getUI();


	daysOfWeek = game->getDaysOfWeek();

	firstNamesM = game->getFirstNamesM();
	firstNamesF = game->getFirstNamesF();
	lastNames = game->getLastNames();

	reasons = game->getReasons();
	reasonsShort = game->getReasonsShort();

	passportPhotos = game->getPassportPhotos();

	currentDay = game->getCurrentDay();
	crittersPerDay = game->getCrittersPerDay();

	std::cout << "playingState CONSTRUCTED AT: " << this << std::endl;

}
PlayingState::~PlayingState()
{
	std::cout << "playingState DESTROYED AT: " << this << std::endl;
}
bool PlayingState::init()
{
	officeBack.getImageFromPath("../Data/assets/crossing/UI/grey office back.png");
	officeBack.setPosition(0, 0);

	background.getImageFromPath("../Data/assets/crossing/UI/crossing background.png");
	background.setPosition(0, 0);

	UI->speechBubble.getImageFromPath("../Data/assets/crossing/UI/speech bubble.png");
	UI->speechBubble.setPosition(80, 57);

	yesStamp.getImageFromPath("../Data/assets/crossing/UI/yes stamp.png");
	noStamp.getImageFromPath("../Data/assets/crossing/UI/no stamp.png");

	// Initialize passport
	passport.getImageFromPath("../Data/assets/crossing/UI/closed passport.png");
	passport.setPosition(100, 205);
	passportPhoto.getImageFromPath("../Data/assets/crossing/critters/frog passport photo.png");

	// Initialize text objects with font from Game
	sf::Font& font = game->getFont();

	namePPtext.setFont(font);
	namePPtext.setString("NAME:");
	namePPtext.setCharacterSize(9);
	namePPtext.setFillColor(sf::Color(55, 55, 55));

	reasonPPtext.setFont(font);
	reasonPPtext.setString("REASON:");
	reasonPPtext.setCharacterSize(9);
	reasonPPtext.setFillColor(sf::Color(55, 55, 55));

	dayPPtext.setFont(font);
	dayPPtext.setString("DAY:");
	dayPPtext.setCharacterSize(9);
	dayPPtext.setFillColor(sf::Color(55, 55, 55));

	nameSpeechText.setFont(font);
	nameSpeechText.setCharacterSize(10);
	nameSpeechText.setFillColor(sf::Color(55, 55, 55));
	nameSpeechText.setPosition(UI->speechBubble.sprite.getPosition().x + 5, UI->speechBubble.sprite.getPosition().y + 3);

	reasonSpeechText.setFont(font);
	reasonSpeechText.setCharacterSize(10);
	reasonSpeechText.setFillColor(sf::Color(55, 55, 55));
	reasonSpeechText.setPosition(UI->speechBubble.sprite.getPosition().x + 5, UI->speechBubble.sprite.getPosition().y + 17);

	calendarText.setFont(font);
	calendarText.setCharacterSize(15);
	calendarText.setFillColor(sf::Color(55, 55, 55));
	calendarText.setPosition(UI->calendar.sprite.getPosition().x + 13, UI->calendar.sprite.getPosition().y + 3);

	// Initialize sounds
	if (!buttonPressBuffer.loadFromFile("../Data/assets/sound/keyPress.wav"))
	{
		std::cout << "Error loading button press sound\n";
	}
	buttonPressSound.setBuffer(buttonPressBuffer);

	if (!stampPressBuffer.loadFromFile("../Data/assets/sound/stampSound.wav"))
	{
		std::cout << "Error loading stamp sound\n";
	}
	stampSound.setBuffer(stampPressBuffer); // Fixed: was stampSoundsetBuffer

	selectCritter();
	critter.setPosition(78 - 178, 97);

	return true;
}
void PlayingState::update(float dt)
{

	UI->UpdateUI(dt, passport.sprite.getPosition(), passportOpened);

	calendarText.setPosition(UI->calendar.sprite.getPosition().x + 13, UI->calendar.sprite.getPosition().y + 3);

	yesStamp.setPosition(passport.sprite.getPosition().x + 44, passport.sprite.getPosition().y + 18);
	noStamp.setPosition(passport.sprite.getPosition().x + 44, passport.sprite.getPosition().y + 18);




	if (UI->yesButtonDown)
	{
		UI->ButtonTimer += dt;
		if (UI->ButtonTimer >= ButtonPressedTime)
		{
			UI->yesButton.getImageFromPath("../Data/assets/crossing/UI/yes button.png");
			UI->yesButtonDown = false;
			UI->ButtonTimer = 0.0f;

		}
	}

	// track if button has been pressed
	if (UI->noButtonDown)
	{
		UI->ButtonTimer += dt;
		if (UI->ButtonTimer >= ButtonPressedTime)
		{
			UI->noButton.getImageFromPath("../Data/assets/crossing/UI/no button.png");
			UI->noButtonDown = false;
			UI->ButtonTimer = 0.0f;
		}
	}

	// track if button has been pressed
	if (UI->nextButtonPressed)
	{

		UI->ButtonTimer += dt;
		if (UI->ButtonTimer >= ButtonPressedTime)
		{
			UI->nextButton.getImageFromPath("../Data/assets/crossing/UI/next button.png");
			UI->nextButtonPressed = false;
			UI->ButtonTimer = 0.0f;
			UI->stampMoveRight = true;

			game->newDay();

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

	


	float distanceX = UI->stamp.sprite.getPosition().x - passport.sprite.getPosition().x;
	float distanceY = UI->stamp.sprite.getPosition().y - passport.sprite.getPosition().y;

	float toloranceX = 50.f;
	float toloranceY = 50.f;

	sf::Vector2f stampCenter(
		UI->stamp.sprite.getPosition().x + UI->stamp.sprite.getGlobalBounds().width / 2.f,
		UI->stamp.sprite.getPosition().y + UI->stamp.sprite.getGlobalBounds().height / 2.f
	);

	sf::Vector2f passportCenter(
		passport.sprite.getPosition().x + passport.sprite.getGlobalBounds().width / 2.f,
		passport.sprite.getPosition().y + passport.sprite.getGlobalBounds().height / 2.f
	);

	sf::FloatRect stampBounds = UI->stamp.sprite.getGlobalBounds();
	bool passportCenterInStamp = stampBounds.contains(passportCenter);


	if (UI->stampDown && passportCenterInStamp && !UI->stampPressed)
	{
		if (UI->yesButtonPressed)
		{
			yesStamp.setVisible(true);
			noStamp.setVisible(false);
			UI->stampPressed = true;
			UI->yesStampApplied = true;
			UI->noStampApplied = false;
		}
		else if (UI->noButtonPressed)
		{
			noStamp.setVisible(true);
			yesStamp.setVisible(false);
			UI->stampPressed = true;
			UI->noStampApplied = true;
			UI->yesStampApplied = false;
		}
	}

	if (UI->stampDown)
	{
		UI->ButtonTimer += dt;
		if (UI->ButtonTimer >= stampPressedTime)
		{
			UI->stamp.getImageFromPath("../Data/assets/crossing/UI/stamp.png");
			UI->stampDown = false;
			UI->ButtonTimer = 0.0f;

		}
	}

	if (crittersSeen >= crittersPerDay)
	{
		game->newDay();
	}



	Game mouseClicked(sf::RenderWindow& window, sf::Event event);



	nameSpeechText.setString(nameDialogue);
	reasonSpeechText.setString(reasonDialogue);
	calendarText.setString(daysOfWeek[currentDay]);




};
void PlayingState::render(sf::RenderWindow& window)
{






	// office back shows behind the main game backgroudnd
	UI-> officeBack.render(window);

	critter.render(window);


	background.render(window);

	// buttons render
	UI->yesButton.render(window);
	UI->noButton.render(window);
	UI->nextButton.render(window);

	UI->calendar.render(window);
	window.draw(calendarText);

	if (critterInPosition)
	{
		UI->speechBubble.render(window);
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

			if (UI->yesStampApplied)
			{

				yesStamp.render(window);

			}
			if (UI->noStampApplied)
			{
				noStamp.render(window);
			}

		}

	}



	// passport, photo, and deta render


	UI->stampShadow.render(window);
	UI->stamp.render(window);
	UI->stampTab.render(window);









};
int PlayingState::selectCritter() {

	if (crittersSeen >= crittersPerDay)
	{
		game->newDay();
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
void PlayingState::generatePassportDetails()
{
	int missmatchChance = rand() % 8;

	passportFirstName = firstName;
	passportLastName = lastName;
	passportReason = reasonDialoge;
	passportDay = daysOfWeek[currentDay];



	// Changes name on passport to be incorrect
	if (missmatchChance == 1)
	{
		std::cout << "------------------\nname mismatch - DENY\n";

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
void PlayingState::generateDialougeDetails()
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



