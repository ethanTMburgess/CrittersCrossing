
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

  void generatePassportDetails();

 private:

  //Text items for passport
  sf::Text namePPtext;
  sf::Text datePPtext;
  sf::Text reasonPPtext;

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

  bool yesButtonDown = false;
  bool noButtonDown = false;
  bool stampDown = false;

  bool yesButtonPressed = false;
  bool noButtonPressed = false;
  bool nextButtonPressed = false;	
  bool stampPressed = false;

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


  // Storing possible names and reasons for entry
  std::string firstNamesM[3] = { "Fred", "Eliot", "Logan"};

  std::string firstNamesF[2] = { "Willow", "Olivia"};

  std::string lastNames[5] = { "Thistledew", "Oakburrow", "Bramblesnout", "Nettlebrook", "WillowTail" };

  std::string reasons[5] = { "trade acorns", "visit the forrest fair", "fix a broken cart wheel", "meet a freind for tea", "meet somebody by the old well" };

  // storing all days of the week for the calendar
  std::string daysOfWeek[7] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };

  GameObject* objectDragged = nullptr;
  sf::Vector2f dragOffset;
 
  

  sf::RenderWindow& window;
  sf::Sprite ball;
  sf::Texture ball_texture;
  sf::Font font;

};

#endif // PLATFORMER_GAME_H
