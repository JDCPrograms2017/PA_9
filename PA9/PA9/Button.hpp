#pragma once

#include <SFML/Graphics.hpp>

class Button : public sf::RectangleShape {

public:
	Button(const sf::Vector2f& newSize = sf::Vector2f(0, 0), const sf::Vector2f& newPos = sf::Vector2f(0, 0), const sf::Texture& newButtonTexture) : sf::RectangleShape(newSize), position(newPos), buttonTexture(newButtonTexture) {
		toggle = false;
	};

	void toggleButton();

	bool getButtonState();
private:
	sf::Vector2f size;
	sf::Vector2f position;
	sf::Texture buttonTexture;
	bool toggle;

};