
#ifndef PLATFORMER_GAME_H
#define CrittersCrossing

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Vector2.h"
#include <Windows.h>
#include <cmath>
#include <SFML/Audio.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  bool collisionCheck(const sf::Vector2f& click, GameObject& object);
  void keyPressed(sf::Event event);
  void mousePressed(sf::Event event);
  void mouseMoved(sf::Event event);
  void mouseReleased(sf::Event event);

  int selectCritter();

  void generateDialougeDetails();

  void generatePassportDetails();

  void newDay();

 private:

  //Text items for passport
  sf::Text namePPtext;
  sf::Text dayPPtext;
  sf::Text reasonPPtext;

  sf::Text calendarDayText;

  sf::Text nameSpeechText;
  sf::Text reasonSpeechText;

  //sound

  sf::SoundBuffer buttonPressBuffer;
  sf::SoundBuffer stampPressBuffer;


  sf::Sound buttonPressSound;
  sf::Sound	stampSound;

  sf::Music BackgroundMusic;
  


  GameObject officeBack;
  GameObject background;

  GameObject passport;
  GameObject passportPhoto;

  GameObject critter;

  GameObject yesButton;
  GameObject noButton;
  GameObject nextButton;

  GameObject stamp;
  GameObject stampTab;
  GameObject stampShadow;

  GameObject yesStamp;
  GameObject noStamp;

  GameObject calendar; 
  sf::Text calendarText;

  GameObject speechBubble;
 
  

  bool yesButtonDown = false;
  bool noButtonDown = false;
  bool stampDown = false;

  bool yesButtonPressed = false;
  bool noButtonPressed = false;
  bool nextButtonPressed = false;	
  bool stampPressed = false;

  bool critterInPosition = false;

  bool hover = false;
  bool pressed = false;
  bool passportDragged = false;
  bool passportOpened = false;
  bool inMenu = false;
  bool critterMoveLeft = false;

  bool yesStampApplied = false;
  bool noStampApplied = false;

  bool stampMoveLeft = false;
  bool stampMoveRight = false;

  bool stampShowing = false;

  float ButtonTimer = 0.0f;

  bool isMale = false;

  //to determine if the critter should be allowed through
  bool passportValid = false;

  bool hasGeneratedDialougeDetails = false;
  bool hasGeneratedPassportDetails = false;
  
  int crittersSeen = 0;
  int currentCritter = 0;
  int currentDay = 6;

  int dayScore = 0;

  int money = 0;

  float ButtonPressedTime = 0.2f;
  float stampPressedTime = 0.35f;

  const float windowWidth = 570.0f;
  const float stampWidth = 167.0f;	
  const float tabWidth = 15.0f;
  const float stampSpeed = 25.0f;
  const float stampVisible = windowWidth - stampWidth;
  const float stampHidden = windowWidth;

  std::string firstName;
  std::string lastName;
  std::string reason;
  std::string day;

  std::string nameDialogue;
  std::string reasonDialogue;

  std::string reasonDialoge;

  std::string newFirstName;
  std::string newLastName;
  std::string newReason;

  std::string lastFirstName;
  std::string lastLastName;
  std::string lastReason;

  std::string passportFirstName;
  std::string passportLastName;
  std::string passportReason;
  std::string passportDay;

  


  // Storing possible names and reasons for entry
  std::string firstNamesM[3] = { "Fred", "Eliot", "Logan"};

  std::string firstNamesF[2] = { "Willow", "Olivia"};

  std::string lastNames[5] = { "Thistledew", "Oakburrow", "Bramblesnout", "Nettlebrook", "Fuzztail" };

  std::string reasons[5] = { "\ntrade acorns", "\nvisit the forest fair", "fix \na broken cart wheel", "\nvisit the shops", "\nmeet somebody by the old well" };

  std::string reasonsShort[5] = { "Business", "Tourism", "Work", "Shopping" ,"Social",};

  std::string passportPhotos[5] = { "../Data/assets/crossing/critters/frog passport image.png",
								   "../Data/assets/crossing/critters/mouse passport image.png",
								   "../Data/assets/crossing/critters/duck passport image.png",
								   "../Data/assets/crossing/critters/racoon passport image.png",
								   "../Data/assets/crossing/critters/rabbit passport image.png" };

  // storing all days of the week for the calendar
  std::string daysOfWeek[7] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

  GameObject* objectDragged = nullptr;
  sf::Vector2f dragOffset;
 
  

  sf::RenderWindow& window;
  sf::Sprite ball;
  sf::Texture ball_texture;
  sf::Font font;

};

#endif // PLATFORMER_GAME_H
