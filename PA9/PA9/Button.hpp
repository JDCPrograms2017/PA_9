#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Button : public sf::RectangleShape {

public:
	Button(const sf::Vector2f& newSize = sf::Vector2f(0, 0), const sf::Vector2f& newPos = sf::Vector2f(0, 0), const sf::Texture& newButtonTexture = sf::Texture()) : sf::RectangleShape(newSize), position(newPos), buttonTexture(newButtonTexture) {
		toggle = false;
		this->setTexture(&buttonTexture);
		std::cout << "New button created!\n";
	};

	void toggleButton();

	bool getButtonState();
	sf::RectangleShape& getDrawableShape();
private:
	sf::Vector2f size;
	sf::Vector2f position;
	const sf::Texture buttonTexture;
	bool toggle;

};