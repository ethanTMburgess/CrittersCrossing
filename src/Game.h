
#ifndef PLATFORMER_GAME_H
#define CrittersCrossing

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Vector2.h"
#include <Windows.h>
#include <cmath>

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

 private:


  GameObject officeBack;
  GameObject background;
  GameObject passport;
  GameObject critter;
  GameObject yesButton;
  GameObject noButton;
  GameObject nextButton;

  bool yesButtonPressed = false;
  bool noButtonPressed = false;	
  bool nextButtonPressed = false;	
  bool hover;
  bool pressed = false;
  bool passportDragged = false;
  bool passportOpened = false;
  bool inMenu = false;
  bool critterMoveLeft = false;

  float ButtonTimer = 0.0f;

  float ButtonPressedTime = 0.2f;

  GameObject* objectDragged = nullptr;
  sf::Vector2f dragOffset;
 
  

  sf::RenderWindow& window;
  sf::Sprite ball;
  sf::Texture ball_texture;

};

#endif // PLATFORMER_GAME_H
