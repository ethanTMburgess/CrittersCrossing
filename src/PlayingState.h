#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

#include"GameObject.h"

class Game;
class UImanager;

class PlayingState
{
public:
    PlayingState(Game* game);
    ~PlayingState();

    bool init();
    void update(float dt);
    void render(sf::RenderWindow& window);

    int getDayScore() const { return dayScore; }

   

    bool getPassportValid() const { return passportValid; }
    
    int selectCritter();
    void generateDialougeDetails();
    void generatePassportDetails();


    sf::Text namePPtext;
    sf::Text dayPPtext;
    sf::Text reasonPPtext;
    sf::Text nameSpeechText;
    sf::Text reasonSpeechText;
    sf::Text calendarText;

    GameObject passport;

    bool passportValid = false;
    bool passportOpened = false;

    sf::SoundBuffer buttonPressBuffer;
    sf::SoundBuffer stampPressBuffer;
    sf::Sound buttonPressSound;
    sf::Sound stampSound;

    bool critterInPosition = false;
    bool passportDragged = false;

    bool critterMoveLeft = false;
    bool isMale = false;

    bool hasGeneratedDialougeDetails = false;
    bool hasGeneratedPassportDetails = false;
    

    

    bool hover = false;

    int crittersSeen = 0;

    int dayScore = 0;
private:
    Game* game;
    UImanager* UI;
   

   

    // Game Objects
    GameObject background;
    GameObject officeBack;
    GameObject yesStamp;
    GameObject noStamp;
    GameObject passportPhoto;
    GameObject critter;

    // Text objects
  

    // State variables
    
    

    // Game data
    
   
   int currentCritter = 0;
    
   int currentDay = 0;
    int crittersPerDay = 1;
   

    // Strings
    std::string firstName;
    std::string lastName;
    std::string reason;
    std::string nameDialogue;
    std::string reasonDialogue;
    std::string reasonDialoge;
    std::string newReason;
    std::string lastReason;
    std::string passportFirstName;
    std::string passportLastName;
    std::string passportReason;
    std::string passportDay;

    
    

    // Timers
    float ButtonPressedTime = 0.2f;
    float stampPressedTime = 0.35f;

    // Dragging
    GameObject* objectDragged = nullptr;
    sf::Vector2f dragOffset;

    std::string* daysOfWeek;
    std::string* firstNamesM;
    std::string* firstNamesF;
    std::string* lastNames;
    std::string* reasons;
    std::string* reasonsShort;
    std::string* passportPhotos;

   

    // Methods
    
};