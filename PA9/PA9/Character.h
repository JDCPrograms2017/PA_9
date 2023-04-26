#pragma once

#include <SFML/Graphics.hpp>

class Character : public sf::Sprite {

public:

	// Generic Character Constructor
	// Takes in a Texture object reference for visuals and an Vector2f object for scale and position.
	Character(const sf::Texture& newTexture = sf::Texture(), const sf::Vector2f& scale = sf::Vector2f(0, 0), const sf::Vector2f& position = sf::Vector2f(0, 0)) : sf::Sprite(newTexture) {
		this->setScale(scale); // goes into sf::Sprite to adjust the scale
		this->setPosition(position);
		interestLevel = 0;
		numQuestionsCorrect = 0;
		numQuestionsIncorrect = 0;
		correctToIncorrectRatio = 0.0;
	}
	
	/*
	* Name: set_the_Position
	* Description: Alters the position of the Character within the window it's displayed in.
	* Inputs: A const copy of an Vector2f object
	*/
	void set_the_Position(const sf::Vector2f position)
	{
		this->setPosition(position);
	}

	/*
	* Name: getDrawableObject
	* Description: Returns a reference to an Sprite object which can then be drawn to the screen.
	* Returns: A reference to an Sprite object
	*/
	sf::Sprite& getDrawableObject() {
		return dynamic_cast<sf::Sprite&>(*this);
	}
	
	// setters written by Simon
	void set_interest(int x)
	{
		interestLevel = x;
	}
	int get_interest() {
		return interestLevel;
	}
private:
	int interestLevel;
	int numQuestionsCorrect;
	int numQuestionsIncorrect;
	float correctToIncorrectRatio;
};