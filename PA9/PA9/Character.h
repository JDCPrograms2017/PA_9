#pragma once

#include <SFML/Graphics.hpp>

class Character : public sf::Sprite {

public:
	Character(const sf::Texture& newTexture, const sf::Vector2f& scale, const sf::Vector2f& position) : sf::Sprite(newTexture) {
		this->setScale(scale); // goes into sf::Sprite to adjust the scale
		this->setPosition(position);
		interestLevel = 0;
		numQuestionsCorrect = 0;
		numQuestionsIncorrect = 0;
		correctToIncorrectRatio = 0.0;
	}

	sf::Sprite& getDrawableObject() {
		return dynamic_cast<sf::Sprite&>(*this);
	}

private:
	int interestLevel;
	int numQuestionsCorrect;
	int numQuestionsIncorrect;
	float correctToIncorrectRatio;
};