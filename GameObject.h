#pragma once
#pragma once

#ifndef PLATFORMER_GAMEOBJECT_H
#  define PLATFORMER_GAMEOBJECT_H
#  include "Vector2.h"
#  include <SFML/Graphics.hpp>

class GameObject
{
public:
	GameObject();
	bool getImageFromPath(std::string _path);
	void render(sf::RenderWindow& _window);
	sf::Sprite* getSprite();

	void setPosition(float x, float y);
	void getPosition();

	sf::Vector2f getPlayerPosition();
	void update(float dt);
	void move(float offset_x, float offset_y);
	bool WindowRightCollide(sf::RenderWindow& _window);
	bool WindowLeftCollide(sf::RenderWindow& _window);
	void setVector(float x, float y);
	void setVector(float x, float y, bool normalise);
	Vector2* getVector();
	void setSpeed(float _speed);
	float getSpeed();
	void setVisible(bool visibility);

	float offset_x;
	float offset_y;

	sf::Sprite sprite;
	sf::Texture texture;

private:
	Vector2 vector;

	float speed = 0;
	bool visible;

};

#endif // PLATFORMER_GAMEOBJECT_H
