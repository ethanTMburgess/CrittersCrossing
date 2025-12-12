#include "GameObject.h"
#include "Game.h"
#include "Vector2.h"
#include <SFML/Graphics.hpp>
#include <iostream>

GameObject::GameObject() : visible (true)
{
    
}




bool GameObject::getImageFromPath(std::string _path)
{
    if (!texture.loadFromFile(_path))
    {
        std::cout << "texture failed to load";
        return false;
    }
    sprite.setTexture(texture);
    visible = true;
    return true;
}

void GameObject::render(sf::RenderWindow& _window)
{
    
    if (!visible) return;
    if (sprite.getTexture() == nullptr) return;
    _window.draw(sprite);
}

void GameObject::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

void GameObject::getPosition()
{
    sprite.getPosition().x;
    sprite.getPosition().y;
}

sf::Vector2f GameObject::getPlayerPosition()
{
    return sprite.getPosition();
}

void GameObject::move(float offset_x, float offset_y)
{
    sprite.move(offset_x, offset_y);
}

bool GameObject::WindowRightCollide(sf::RenderWindow& _window)
{
    // if obj hits Right of screen
    if (
        sprite.getPosition().x + 10 >
        (_window.getSize().x - sprite.getGlobalBounds().width))
    {
        std::cout << "Right collision detected\n";
        return true;
    }
    return false;
}

bool GameObject::WindowLeftCollide(sf::RenderWindow& _window)
{
    // if obj hits left of screen
    if (sprite.getPosition().x - 10 < 0)
    {
        std::cout << "left collision detected\n";
        return true;
    }
    return false;
}

void GameObject::setVector(float x, float y)
{
    vector.x = x;

    vector.y = y;
}

void GameObject::setVector(float x, float y, bool normalise)
{
    vector.x = x;

    vector.y = y;

    if (normalise)
    {
        vector.normalise();
    }
}

Vector2* GameObject::getVector()
{
    return &vector;
}

void GameObject::setSpeed(float _speed)
{
    speed = _speed;
}

float GameObject::getSpeed()
{
    return speed;
}

void GameObject::update(float dt) {}

void GameObject::setVisible(bool visibility)
{
    visible = visibility;
}

sf::Sprite* GameObject::getSprite()
{
    return &sprite;
}

// player actions on key command
void Game::keyPressed(sf::Event event)
{
    // if player presses D
    if (event.key.code == sf::Keyboard::D) 
    {

    }
}


