#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

class Button : public sf::RectangleShape {

public:
	Button(const sf::Vector2f& newSize = sf::Vector2f(0, 0), const sf::Vector2f& newPos = sf::Vector2f(0, 0), const sf::Texture& newButtonTexture = sf::Texture()) : sf::RectangleShape(newSize), position(newPos), buttonTexture(newButtonTexture) {
		toggle = false;
		dynamic_cast<sf::RectangleShape&>(*this).setTexture(&buttonTexture);
		std::cout << "New button created!\n";
		this->setPosition(position);
	};

	void toggleButton();
	void setPosition(sf::Vector2f &newPosition);
	void changeButtonTexture(sf::Texture& newTexture);

	bool getButtonState();
	bool isBeingPushed(const sf::Window &windowRef);
	sf::RectangleShape& getDrawableShape();
private:
	sf::Vector2f position;
	const sf::Texture buttonTexture;
	bool toggle;

};