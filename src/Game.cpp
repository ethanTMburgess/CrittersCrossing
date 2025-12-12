#include "Game.h"
#include "GameObject.h"
#include "UImanager.h"
#include "PlayingState.h"
#include "DayEndState.h"
#include "MenuState.h"
#include <iostream>
#include <cstdlib>
#include <ctime>







Game::Game(sf::RenderWindow& game_window)
	: window(game_window)
{
	srand(time(NULL));

	UI = std::make_unique<UImanager>();
	playing = std::make_unique<PlayingState>(this);
	dayEnd = std::make_unique<DayEndState>(this);
	menu = std::make_unique<MenuState>(this);

	UI->setgame(this);
	UI->setPlayingState(playing.get());


}

Game::~Game()
{
	


}

bool Game::init()
{

	currentState = GameState::MENU;
	

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

	// UImanager* mouseClicked();

	UI->initMenuUI();
	dayEnd->init();
	UI->initdayEndUI();

	sf::Vector2f stampBasePosition = UI->stamp.sprite.getPosition();




	UI->nextDayButton.getImageFromPath("../Data/assets/crossing/UI/power button.png");
	UI->nextDayButton.setPosition(414, 134);


	return true;


}

void Game::update(float dt)
{

	switch (currentState)
	{
	case GameState::MENU:
		menu->update(dt);
		break;

	case GameState::PLAYING:
		playing->update(dt);
		break;

	case GameState::DAYEND:
		dayEnd->update(dt);
		break;

	default:
		break;
	}


	if (currentState == GameState::PLAYING)
	{

		// std::cout << "updating handling new day / critter spawn\n";
		if (playing->shouldCreateNewDay())
		{
			playing->TryEventClear();
			newDay();

		}
		else if (playing->shouldSpawnCritter())
		{
			playing->TryEventClear();
			playing->selectCritter();
			playing->critter.setPosition(78 - 178, 97);


			playing->critterMoveLeft = false;

			playing->critterInPosition = false;

		}
	}

}

void Game::render()
{



	switch (currentState)
	{
	case GameState::MENU:
		// UI->initMenuUI();
		UI->renderMenuUI(window);
		menu->init();
		menu->render(window);
		break;

	case GameState::PLAYING:
		playing->render(window);
		UI->renderPlayingUI(window, playing->passportOpened);
		break;

	case GameState::DAYEND:
		//dayEnd->init();
		dayEnd->render(window);
		UI->initdayEndUI();
		UI->renderDayEndUI(window);
		break;

	}






}







void Game::mousePressed(sf::Event event)
{

	if (UI)
	{
		UI->mouseClicked(window, event);
	}

	sf::Vector2i pixelClick{ event.mouseButton.x, event.mouseButton.y };
	sf::Vector2f worldClick = window.mapPixelToCoords(pixelClick);

	if (collisionCheck(worldClick, playing->passport))
	{
		objectDragged = &playing->passport;

		sf::Sprite* sprite = objectDragged->getSprite();
		sf::Vector2f objectPos = sprite->getPosition();
		dragOffset = worldClick - objectPos;

		passportDragged = true;
		//std::cout << "presssssed\n";
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

		//std::cout << "drraaaaaagged\n";

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



	//std::cout << "releaaaaased\n";

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


	playing->selectCritter();

	playing->generateDialougeDetails();
	playing->generatePassportDetails();

	playing->critter.setPosition(78 - 178, 97);
	playing->critterMoveLeft = false;
	playing->critterInPosition = false;
	currentState = GameState::DAYEND;
	money = money + dayScore * 5;
	std::cout << "\n\n------------\n\nDay Score: " << dayScore << "\nTotal Money: $" << money << "\n\n------------\n\n" << std::endl;

	if (dayEnd)
	{
		dayEnd -> init();

	}
	if (UI)
	{
		UI->initdayEndUI();
	}

}







void Game::renderMenu()
{

}



void Game::renderDayEnd()
{


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






bool Game::collisionCheck(const sf::Vector2f& click, GameObject& object)
{

	sf::Sprite* sprite = object.getSprite();

	if (!sprite)
	{
		std::cout << "CRITICAL: sprite pointer is null!" << std::endl;
		return false;
	}

	// Check if the sprite's texture pointer is valid
	const sf::Texture* texture = sprite->getTexture();

	
	if (texture == nullptr)
	{
		std::cout << "CRITICAL: sprite texture is null!" << std::endl;
		return false;
	}

	// Check if the texture pointer looks corrupted (pointing to garbage memory)
	if (reinterpret_cast<uintptr_t>(texture) < 0x1000) // Too low address
	{
		std::cout << "CRITICAL: texture pointer is corrupted (low address)!" << std::endl;
		return false;
	}

	// Now safely get bounds
	try
	{
		sf::FloatRect bounds = sprite->getGlobalBounds();
		return bounds.contains(click.x, click.y);
	}
	catch (...)
	{
		std::cout << "CRITICAL: Exception getting sprite bounds!" << std::endl;
		return false;
	}
}


