
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

  bool hasGeneratedDialougeDetails = false;
  bool hasGeneratedPassportDetails = false;
  

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

  std::string reasonPassport;

  std::string newFirstName;
  std::string newLastName;
  std::string newReason;

  std::string lastFirstName;
  std::string lastLastName;
  std::string lastReason;

  


  // Storing possible names and reasons for entry
  std::string firstNamesM[3] = { "Fred", "Eliot", "Logan"};

  std::string firstNamesF[2] = { "Willow", "Olivia"};

  std::string lastNames[5] = { "Thistledew", "Oakburrow", "Bramblesnout", "Nettlebrook", "Fuzztail" };

  std::string reasons[5] = { "\ntrade acorns", "\nvisit the forrest fair", "fix \na broken cart wheel", "\nvisit the shops", "\nmeet somebody by the old well" };

  std::string reasonsShort[5] = { "Business", "Tourism", "Work", "Shopping" ,"Scoial",};

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
