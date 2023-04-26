#pragma once

#include <SFML/Graphics.hpp>

class Character : public sf::Sprite {

public:
	Character(const sf::Texture& newTexture = sf::Texture(), const sf::Vector2f& scale = sf::Vector2f(0, 0), const sf::Vector2f& position = sf::Vector2f(0, 0)) : sf::Sprite(newTexture) {
		this->setScale(scale); // goes into sf::Sprite to adjust the scale
		this->setPosition(position);
		interestLevel = 0;
		numQuestionsCorrect = 0;
		numQuestionsIncorrect = 0;
		correctToIncorrectRatio = 0.0;
	}
	
	void set_the_Position(const sf::Vector2f position)
	{
		this->setPosition(position);
	}

	sf::Sprite& getDrawableObject() {
		return dynamic_cast<sf::Sprite&>(*this);
	}
	
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