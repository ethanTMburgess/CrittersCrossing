#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "UImanager.h"
#include "GameObject.h"
#include <windows.h>


// test change
int main()
{
  std::cout << "You should see a window that opens as well as this writing to console..."
            << std::endl;

  SetProcessDPIAware(); // to stop blurriness on high res screens

  // create window and set up
  sf::RenderWindow window(sf::VideoMode(570, 320), "Critters Crossing");
  sf::Font font;
  font.loadFromFile("../Data/Fonts/PixelifySans-Regular.ttf");


  sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
  window.setView(view);


  sf::Image icon;
  if(icon.loadFromFile("../Data/assets/crossing/critters/frog portrait.png"))
  {
      window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
  }
  window.setFramerateLimit(60);
  
 
  //initialise an instance of the game class
  Game game(window);
  UImanager UI;
 

  //run the init function of the game class and check it all initialises ok
  if (!game.init())
  {
    return 0;
  }

  // A Clock starts counting as soon as it's created
  sf::Clock clock;

  // Game loop: run the program as long as the window is open
  while (window.isOpen())
  {
      // check all the window's events that were triggered since the last iteration of the loop
      sf::Event event;

      //calculate delta time
      sf::Time time = clock.restart();
      float dt = time.asSeconds();

      //'process inputs' element of the game loop
      while (window.pollEvent(event))
      {
          // "close requested" event: we close the window
          if (event.type == sf::Event::Closed)
              window.close();

          if (event.key.code == sf::Keyboard::Space)
          {
			  game.keyPressed(event);
          }

          if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
          {
              //UI.mouseClicked(window, event);
              game.mousePressed(event);

          }


          if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
          {
              game.mouseReleased(event);

              
          }

          
          if (event.type == sf::Event::MouseMoved)
          {
              game.mouseMoved(event);
          }



         
          
      }

      game.update(dt);
      window.clear(sf::Color::Black);
      game.render();
      window.display();

      

      
  }

  
 

  return 0;
}
